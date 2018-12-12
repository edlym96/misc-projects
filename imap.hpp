#ifndef IMAP_H
#define IMAP_H
#include "imaputils.hpp"
#include <libetpan/libetpan.h>
#include <string>
#include <functional>
#include <iostream>


namespace IMAP {
  class Session;
  
class Message {
  Session* session;
  uint32_t uid;
public:
  Message(Session* sess, uint32_t uid_no);
  /**
   * Get the body of the message. You may chose to either include the headers or not.
   */
  std::string getBody();
  /**
   * Get one of the descriptor fields (subject, from, ...)
   */
  std::string getField(std::string fieldname);
  /**
   * Remove this mail from its mailbox
   */
  std::string getMessageContent(mailimap_msg_att* msg_att);
  void parseString(std::string & mainStr, const std::string & toErase);
	void deleteFromMailbox();
  ~Message();
};

class Session {
  bool logged_in;
  int number_of_messages;
public:
  struct mailimap *imap;
  std::function<void()> refreshFunction;
	Session(std::function<void()> updateUI);
  
	/**
	 * Get all messages in the INBOX mailbox terminated by a nullptr (like we did in class)
	 */
	Message** getMessages();

	/**
	 * connect to the specified server (143 is the standard unencrypte imap port)
	 */
	void connect(std::string const& server, size_t port = 143);

	/**
	 * log in to the server (connect first, then log in)
	 */
	void login(std::string const& userid, std::string const& password);

	/**
	 * select a mailbox (only one can be selected at any given time)
	 * 
	 * this can only be performed after login
	 */
	void selectMailbox(std::string const& mailbox);

	~Session();
};
}

#endif /* IMAP_H */
