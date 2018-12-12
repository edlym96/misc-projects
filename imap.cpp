#include "imap.hpp"

using namespace IMAP;

Message::Message(Session* sess, uint32_t uid_no):session(NULL), uid(uid_no){
  session = sess;
}

std::string Message::getBody(){
    
  struct mailimap_set * set;
  struct mailimap_section * section;
  struct mailimap_fetch_type * fetch_type;
  struct mailimap_fetch_att * fetch_att;
  int error;
  clist * fetch_result;
  clistiter * cur;
  std::string result;

  set = mailimap_set_new_single(uid);
  fetch_type = mailimap_fetch_type_new_fetch_att_list_empty();
  section = mailimap_section_new(NULL);
  fetch_att = mailimap_fetch_att_new_body_peek_section(section);
  mailimap_fetch_type_new_fetch_att_list_add(fetch_type, fetch_att);

  error = mailimap_uid_fetch(session->imap, set, fetch_type, &fetch_result);
  check_error(error, "could not fetch");
  
  for(cur = clist_begin(fetch_result); cur != NULL; cur = clist_next(cur)){
    struct mailimap_msg_att * msg_att;
    msg_att = (struct mailimap_msg_att*) clist_content(cur);
    result = getMessageContent(msg_att);
  }
  mailimap_fetch_list_free(fetch_result);
  if(result.empty()){
    return NULL;
  }
  return result;
}

std::string Message::getField(std::string fieldname){
  
  clist* headerList = clist_new();

  char* field_name = new char[fieldname.size() + 1];
  std::copy(fieldname.begin(), fieldname.end(), field_name);
  field_name[fieldname.size()] = '\0';
  
  if(clist_append(headerList, field_name) < 0){
    return NULL;
  }
  
  struct mailimap_set * set;
  struct mailimap_fetch_type* fetch_type;
  struct mailimap_fetch_att* fetch_att;
  struct mailimap_header_list* headers; 
  struct mailimap_section* headerSection;
  clist * fetch_result;
  int error;
  std::string result;

  headers = mailimap_header_list_new(headerList);
  headerSection = mailimap_section_new_header_fields(headers);
  set = mailimap_set_new_single(uid);
  fetch_type = mailimap_fetch_type_new_fetch_att_list_empty();
  fetch_att = mailimap_fetch_att_new_body_peek_section(headerSection);
  mailimap_fetch_type_new_fetch_att_list_add(fetch_type, fetch_att);

  error = mailimap_uid_fetch(session->imap, set, fetch_type, &fetch_result);
  check_error(error, "could not fetch");

  clist_free(headerList);
  delete[] field_name;
  
  clistiter * cur;
  for(cur = clist_begin(fetch_result); cur != NULL; cur = clist_next(cur)){
    struct mailimap_msg_att * msg_att;
    msg_att = (struct mailimap_msg_att*) clist_content(cur);
    result = getMessageContent(msg_att);
  }
  mailimap_fetch_list_free(fetch_result);
  parseString(result, fieldname);
  
  if(result.empty()){
    return NULL;
  }
  return result;
 }

std::string Message::getMessageContent(mailimap_msg_att* msg_att){
  clistiter* cur;
  for(cur = clist_begin(msg_att->att_list); cur != NULL; cur = clist_next(cur)){
    struct mailimap_msg_att_item* item;
    item = (struct mailimap_msg_att_item*)clist_content(cur);
    if(item->att_type != MAILIMAP_MSG_ATT_ITEM_STATIC){
      continue;
    }
    if(item->att_data.att_static->att_type != MAILIMAP_MSG_ATT_BODY_SECTION){
      continue;
    }
    return item->att_data.att_static->att_data.att_body_section->sec_body_part;
  }
  return "";
}

void Message::parseString(std::string & mainStr, const std::string & toErase){
  size_t pos = mainStr.find(toErase);

  std::string toErase_full;
  toErase_full.assign(toErase);
  toErase_full += ": ";
  
  if(pos != std::string::npos){
    mainStr.erase(pos, toErase_full.length());
  }

  while(!mainStr.empty() && mainStr[mainStr.size() - 1] == '\r' || mainStr[mainStr.size() - 1] == '\n'){
    mainStr.erase(mainStr.size() - 1);
  }
  
}

void Message::deleteFromMailbox(){
  
  struct mailimap_set * set;
  struct mailimap_flag_list* flag_list;
  struct mailimap_flag* flag_deleted;
  int error;
  
  set = mailimap_set_new_single(uid);
  flag_list = mailimap_flag_list_new_empty();
  flag_deleted = mailimap_flag_new_deleted();
  error = mailimap_flag_list_add(flag_list, flag_deleted);
  check_error(error, "failed to add flag");

  struct mailimap_store_att_flags* store;
  
  store = mailimap_store_att_flags_new_set_flags(flag_list);
  error = mailimap_uid_store(session->imap, set, store);
  check_error(error, "Failed to change message status");
  error = mailimap_expunge(session->imap);
  check_error(error, "Failed to delete message");
  mailimap_store_att_flags_free(store);
  session->refreshFunction();
  
}

Message::~Message(){

}

Session::Session(std::function<void()> updateUI): imap(NULL), logged_in(false), number_of_messages(0), refreshFunction(updateUI){
  imap = mailimap_new(0, NULL);
}

Message** Session::getMessages(){
  
  struct mailimap_set * set;
  struct mailimap_fetch_type * fetch_type;
  struct mailimap_fetch_att * fetch_att_uid;
  struct mailimap_fetch_att * fetch_att_body;
  int error;
  Message** msg_list;
  
  clist * fetch_result;
  clistiter * cur;
  
  set = mailimap_set_new_interval(1,0);
  fetch_type = mailimap_fetch_type_new_fetch_att_list_empty();
  fetch_att_uid = mailimap_fetch_att_new_uid();
  mailimap_fetch_type_new_fetch_att_list_add(fetch_type, fetch_att_uid);
  
  try{
  error = mailimap_fetch(imap, set, fetch_type, &fetch_result);
  check_error(error, "could not fetch");
  }catch(const std::runtime_error& err){
    msg_list = NULL;
    return msg_list;
  }

  number_of_messages = 0;
  
  for(cur = clist_begin(fetch_result); cur != NULL; cur = clist_next(cur)){
    ++number_of_messages;
  }
  
  msg_list = new Message*[number_of_messages+1];
  
  int index = 0;
  
  for(cur = clist_begin(fetch_result); cur != NULL; cur = clist_next(cur)){
    struct mailimap_msg_att * msg_att;
    uint32_t uid;
    clistiter * cur2;
    msg_att = (struct mailimap_msg_att*) clist_content(cur);
    
    for(cur2 = clist_begin(msg_att->att_list); cur2 != NULL; cur2 = clist_next(cur2)){
      auto item = (struct mailimap_msg_att_item*) clist_content(cur2);
      if(item->att_type != MAILIMAP_MSG_ATT_ITEM_STATIC){
	continue;
      }
      if(item->att_data.att_static->att_type != MAILIMAP_MSG_ATT_UID){
	continue;
      }
      uid = item->att_data.att_static->att_data.att_uid;
    }
    msg_list[index] = new Message(this, uid);
    index++;
  }
  
  msg_list[number_of_messages] = NULL;
  mailimap_fetch_list_free(fetch_result);
  
  return msg_list;  
}

void Session::connect(std::string const&server, size_t port){
  int error;
  error = mailimap_socket_connect(imap, server.c_str(), port);
  check_error(error, "Could not connect to server");
}

void Session::login(std::string const& userid, std::string const& password){
  int error;
  error = mailimap_login(imap, userid.c_str(), password.c_str());
  if(!error) logged_in = true;
  check_error(error, "Could not log in");
  return;
}

void Session::selectMailbox(std::string const& mailbox){
  int error;
  if(logged_in){
    error = mailimap_select(imap, mailbox.c_str());
  }
  const std::string message = std::string("Could not access ") + mailbox;
  check_error(error, message.c_str());
  /*
  struct mailimap_status_att_list * status_att_list;
  struct mailimap_mailbox_data_status ** result;

  status_att_list = mailimap_status_att_list_new_empty();
  error = mailimap_status_att_list_add(status_att_list, MAILIMAP_STATUS_ATT_MESSAGES);
  check_error(error, "Could not add status attribute to list");

  error = mailimap_status(imap, mailbox.c_str(), status_att_list, result);

  auto value = ((struct mailimap_status_info*)clist_content(clist_begin((*result)->st_info_list)))->st_value;
  number_of_messages = (int) value;
    
clistiter* cur;
 for(cur = clist_begin((*result)->st_info_list); cur != NULL; cur = clist_next(cur)){
    struct mailimap_status_info* item;
    
    item = (struct mailimap_status_info*)clist_content(cur);
    if(item->st_att = MAILIMAP_STATUS_ATT_MESSAGES){
      number_of_messages = int(item->st_value);
    }
  }
  mailimap_status_att_list_free(status_att_list);
  */
 
}

Session::~Session(){
  int error;
  error = mailimap_logout(imap);
  //check_error(error, "Failed to log out");
  logged_in = false;
  mailimap_free(imap);
  
}
