/*!
 * Copyright by Denys Khanzhiyev aka xdenser
 *
 * See license text in LICENSE file
 */
#ifndef SRC_FB_BINDINGS_FBRESULT_H_
#define SRC_FB_BINDINGS_FBRESULT_H_


class FBResult : public FBEventEmitter {

public:

 static Persistent<FunctionTemplate> constructor_template;
 
 static void
   Initialize (v8::Handle<v8::Object> target);
  
 bool process_result(XSQLDA **sqldap, isc_stmt_handle *stmtp, Local<Array> res);
  
protected:  
 static Handle<Value>
  New (const Arguments& args);
  
  static Local<Value> 
  GetFieldValue(XSQLVAR *var);

  static Handle<Value>
  FetchSync(const Arguments& args);

  struct fetch_request {
     Persistent<Value> rowCallback;
     Persistent<Function> eofCallback;
     FBResult *res;
     int rowCount;
     int fetchStat;
     bool rowAsObject;
  };
  
  static int EIO_After_Fetch(eio_req *req);

  static int EIO_Fetch(eio_req *req);
  
  static Handle<Value>
  Fetch(const Arguments& args);
  
  FBResult (XSQLDA *asqldap, isc_stmt_handle *astmtp); 
  
  ~FBResult();
  
  ISC_STATUS_ARRAY status;
  char err_message[MAX_ERR_MSG_LEN];
  XSQLDA *sqldap;
  isc_stmt_handle stmt;

};

#endif