#include "imap.hpp"

using namespace IMAP;

//**Message constructor sets current seesion and uid number
Message::Message(Session* sess, uint32_t uid_no):session(NULL), uid(uid_no){
  session = sess;
}

//**Function to get the body of a message
std::string Message::getBody(){

  //*Initialise variables
  struct mailimap_set * set;
  struct mailimap_section * section;
  struct mailimap_fetch_type * fetch_type;
  struct mailimap_fetch_att * fetch_att;
  int error;
  clist * fetch_result;
  clistiter * cur;
  std::string result;

  set = mailimap_set_new_single(uid); //Create the uid set based onmessage uid no
  fetch_type = mailimap_fetch_type_new_fetch_att_list_empty(); //Create empty fetch type list
  section = mailimap_section_new(NULL); //Create empty fetch secion
  fetch_att = mailimap_fetch_att_new_body_peek_section(section); //create fetch att based on section
  mailimap_fetch_type_new_fetch_att_list_add(fetch_type, fetch_att); //Add the fetch att to the fetch list

  //*Execute fetch and check error. Result saved into fetch resul
  error = mailimap_uid_fetch(session->imap, set, fetch_type, &fetch_result);
  check_error(error, "could not fetch");

  //*Extract the message content
  for(cur = clist_begin(fetch_result); cur != NULL; cur = clist_next(cur)){
    struct mailimap_msg_att * msg_att;
    msg_att = (struct mailimap_msg_att*) clist_content(cur);
    result = getMessageContent(msg_att);
  }
  //*Free variables and return result
  mailimap_set_free(set);
  mailimap_fetch_list_free(fetch_result);
  if(result.empty()){
    return NULL;
  }
  return result;
}

//**Function to get field
std::string Message::getField(std::string fieldname){
  
  clist* headerList = clist_new();
  //*Convert fieldname from str to char* and add it to a clist
  char* field_name = new char[fieldname.size() + 1];
  std::copy(fieldname.begin(), fieldname.end(), field_name);
  field_name[fieldname.size()] = '\0';
  
  if(clist_append(headerList, field_name) < 0){
    return NULL;
  }

  //*Initialise variables
  struct mailimap_set * set;
  struct mailimap_fetch_type* fetch_type;
  struct mailimap_fetch_att* fetch_att;
  struct mailimap_header_list* headers; 
  struct mailimap_section* headerSection;
  clist * fetch_result;
  int error;
  std::string result;

  headers = mailimap_header_list_new(headerList); //Create fetch header list based on headers
  headerSection = mailimap_section_new_header_fields(headers); //Create fetch section based on headers
  set = mailimap_set_new_single(uid); //Create set based on message uid
  fetch_type = mailimap_fetch_type_new_fetch_att_list_empty(); //Create fetch type list
  fetch_att = mailimap_fetch_att_new_body_peek_section(headerSection); //Create fetch att based on heaedr section
  mailimap_fetch_type_new_fetch_att_list_add(fetch_type, fetch_att); //Add the fetch att to the fetch type list

  //*Execute fetch and add to headers
  error = mailimap_uid_fetch(session->imap, set, fetch_type, &fetch_result);
  check_error(error, "could not fetch");

  //*Free the clist and char array
  clist_free(headerList);
  delete[] field_name;

  //*Extract the header content
  clistiter * cur;
  for(cur = clist_begin(fetch_result); cur != NULL; cur = clist_next(cur)){
    struct mailimap_msg_att * msg_att;
    msg_att = (struct mailimap_msg_att*) clist_content(cur);
    result = getMessageContent(msg_att);
  }

  //*Free the variables
  mailimap_set_free(set);
  mailimap_fetch_list_free(fetch_result);

  //*Parse the string to get desired output
  parseString(result, fieldname);
  
  if(result.empty()){
    return NULL;
  }
  return result;
 }

//*Helper function to get message content from message att
std::string Message::getMessageContent(mailimap_msg_att* msg_att){
  clistiter* cur;
  //*Iterate through msg_att struct to get the message body
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

//**Helper function to parse the string from getField
void Message::parseString(std::string & mainStr, const std::string & toErase){
  size_t pos = mainStr.find(toErase);

  //*Erase the beginning part of the string to get the content only
  std::string toErase_full;
  toErase_full.assign(toErase);
  toErase_full += ": ";
  
  if(pos != std::string::npos){
    mainStr.erase(pos, toErase_full.length());
  }
  //*Remove the end of line characters
  while(!mainStr.empty() && mainStr[mainStr.size() - 1] == '\r' || mainStr[mainStr.size() - 1] == '\n'){
    mainStr.erase(mainStr.size() - 1);
  }
  
}

//**Function to delete from mailbox
void Message::deleteFromMailbox(){
  //*Initialise variables
  struct mailimap_set * set;
  struct mailimap_flag_list* flag_list;
  struct mailimap_flag* flag_deleted;
  int error;

  set = mailimap_set_new_single(uid);//Create set base on message uid
  flag_list = mailimap_flag_list_new_empty();//Create flag lsit
  flag_deleted = mailimap_flag_new_deleted();//Create deleted flag
  error = mailimap_flag_list_add(flag_list, flag_deleted);//Add to the flag list
  check_error(error, "failed to add flag");

  struct mailimap_store_att_flags* store;
  
  store = mailimap_store_att_flags_new_set_flags(flag_list); //Create store based on flag list
  error = mailimap_uid_store(session->imap, set, store); //Change the message status based on store and check for error
  check_error(error, "Failed to change message status");
  error = mailimap_expunge(session->imap);
  check_error(error, "Failed to delete message");
  session->refreshFunction(); //Refresh UI after deleting

  //*Free variables
  mailimap_set_free(set);
  mailimap_store_att_flags_free(store);
}

Message::~Message(){

}

//**Session constructor keeps track of number of messages and msg_list for memory cleanup
Session::Session(std::function<void()> updateUI): imap(NULL), logged_in(false), number_of_messages(0), refreshFunction(updateUI), msg_list(NULL){
  imap = mailimap_new(0, NULL);
}

//*Function to get all messages from the mailbox
Message** Session::getMessages(){
  //*Initialise variables
  struct mailimap_set * set;
  struct mailimap_fetch_type * fetch_type;
  struct mailimap_fetch_att * fetch_att_uid;
  struct mailimap_fetch_att * fetch_att_body;
  int error;
  
  clist * fetch_result;
  clistiter * cur;
  
  set = mailimap_set_new_interval(1,0); //Create set
  fetch_type = mailimap_fetch_type_new_fetch_att_list_empty(); //Create empty fetch list
  fetch_att_uid = mailimap_fetch_att_new_uid();//Create fetch uid att
  mailimap_fetch_type_new_fetch_att_list_add(fetch_type, fetch_att_uid);//Add the fetch att to the fetch list

  number_of_messages = 0; //Reset number of messages

  //*Try to fetch and handle the exception when mailbox is empty
  try{error = mailimap_fetch(imap, set, fetch_type, &fetch_result);
  check_error(error, "could not fetch");
  }catch(const std::runtime_error& err){
    msg_list = new Message*[1];
    msg_list[0] = NULL;
    return msg_list;
  }

  //*For loop to get number of messages in lsit
  for(cur = clist_begin(fetch_result); cur != NULL; cur = clist_next(cur)){
    ++number_of_messages;
  }

  //*Create msg_list array
  msg_list = new Message*[number_of_messages+1];

  //*Index to keep track when adding messages to the message list
  int index = 0;

  //*Iterate through result and create messages with corresponding uid and add to message list
  for(cur = clist_begin(fetch_result); cur != NULL; cur = clist_next(cur)){
    struct mailimap_msg_att * msg_att;
    uint32_t uid;
    clistiter * cur2;
    msg_att = (struct mailimap_msg_att*) clist_content(cur);

    //*Loop to get the uid result
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
    //*Create a new message from corresponding uid and add to msg_list array
    msg_list[index] = new Message(this, uid);
    index++;
  }

  //*Free variables
  msg_list[number_of_messages] = NULL;
  mailimap_set_free(set);
  mailimap_fetch_list_free(fetch_result);
  
  return msg_list;  
}

//**Function to connect to server
void Session::connect(std::string const&server, size_t port){
  int error;
  //*Connecto to server and check for error
  error = mailimap_socket_connect(imap, server.c_str(), port);
  check_error(error, "Could not connect to server");
}

//**Function to login
void Session::login(std::string const& userid, std::string const& password){
  int error;
  //*Log in and check for error. Set logged in status to true if successful
  error = mailimap_login(imap, userid.c_str(), password.c_str());
  if(!error) logged_in = true;
  check_error(error, "Could not log in");
  return;
}

//**Function to set mailbox
void Session::selectMailbox(std::string const& mailbox){
  int error;
  //*Mailbox can only be selected if logged in
  if(logged_in){
    error = mailimap_select(imap, mailbox.c_str());
  }
  //*Select and check for error
  const std::string message = std::string("Could not access ") + mailbox;
  check_error(error, message.c_str());
 
}

//**Session destructor to clean up data structure
Session::~Session(){
  int error;
  error = mailimap_logout(imap);
  //check_error(error, "Failed to log out");
  logged_in = false;
  mailimap_free(imap);
  //*Free dynamically allocated messages in message list
  for(int i = 0; i < number_of_messages; ++i){
    delete msg_list[i];
  }
}
