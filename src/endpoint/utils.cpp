#setLanguageLevel 3;

/*
   Author:     Lars Andreas Ness
   Date:       31.08.2016
   Filename:   "geas_utils.ejs"

   Desc:       Utility library for ejScript. Contains various methods enabling,
              for instance, advanced String-manipulation, XMLNode handling,
              Extra Table helper methods, etc.
 */

Map DB_DATA_TYPES =
	Map()
	.insert("1", "number")             // Integer
	.insert("2", "string")             // Text (long)
	.insert("3", "string")             // Date
	.insert("6", "bool")               // Boolean
	.insert("10", "string")            // Text (short)
	.insert("15", "number")             // Float
	.insert("16", "number")            // Contact relation
	.insert("17", "number")            // Sale relation
	.insert("20", "number")            // Extra table relation
	.insert("22", "number")            // File/attachment relation
	.insert("27", "number");           // User relation

Void Log(String ctx, String message) {
	log("[" + ctx + "] " + message);
}

String Context(String scope, String method) {
	return scope + "." + method;
}

// Wrap injected String {s} to ensure it is formatted as valid JSON string
// TODO: Escape JSON breaking characters (RegEx?)
String str(String s) {
	return "\"" + s + "\"";
}

/*************************** START NODE FUNCTIONS *****************************/
/*
        Node: Constructors
 */

XMLNode ObjectNode(String name) {
	XMLNode node;
	node.setName(name);
	node.setParameter("type", "object");
	return node;
}
XMLNode ObjectNode(String name, XMLNode[] properties) {
	XMLNode node;
	node.setName(name);
	node.setParameter("type", "object");
	node.setChildren(properties);
	return node;
}

XMLNode ArrayNode(String name) {
	XMLNode node;
	node.setName(name);
	node.setParameter("type", "array");
	return node;
}

// XMLNode ArrayItem(String value) {
//      XMLNode node;
//      node.setName(name);
//      node.setParameter("type", "array");
//      return node;
// }

XMLNode Node(String name, String value) {
	XMLNode node;
	node.setName(name);
	node.setText(value);
	node.setParameter("type", "string");
	return node;
}

XMLNode Node(String name, Integer value) {
	XMLNode node;
	node.setName(name);
	node.setText(value.toString());
	node.setParameter("type", "number");
	return node;
}

XMLNode Node(String name, Bool value) {
	XMLNode node;
	node.setName(name);
	node.setText(value.toString());
	node.setParameter("type", "boolean");
	return node;
}

XMLNode Node(String name, Float value, Integer decLength) {
	XMLNode node;
	node.setName(name);
	node.setText(value.toString(decLength));
	node.setParameter("type", "number");
	return node;
}

XMLNode Node(String name, String value, String type) {
	XMLNode node;
	node.setName(name);
	node.setText(value);
	node.setParameter("type", type);
	return node;
}

XMLNode EmptyNode() {
	XMLNode node;
	return node;
}

XMLNode RequestNode(String request, String method, String description) {
	XMLNode res = ObjectNode(request);
	res.addChild(Node("method", method));
	res.addChild(Node("description", description));
	return res;
}

/*
        Node: Getters
 */

XMLNode getNode(XMLNode parent, String nodeName) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (children[i].getName().equalsIgnoreCase(nodeName)) return children[i];
	}
	return EmptyNode();
}

XMLNode getNodeByValue(XMLNode parent, String nodeValue) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (children[i].getText().equals(nodeValue)) return children[i];
	}
	return EmptyNode();
}

String getNodeValue(XMLNode parent, String nodeName) {
	return getNode(parent, nodeName).getText();
}

XMLNode getNodeByIndex(XMLNode parent, Integer index) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (i == index) return children[i];
	}
	return EmptyNode();
}

/*
        Node: Setters
 */

Void setNodeValue(XMLNode parent, String nodeName, String newValue) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (children[i].getName().equalsIgnoreCase(nodeName)) children[i].setText(newValue);
	}
}

Void setNodeValue(XMLNode parent, String nodeName, Integer newValue) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (children[i].getName().equalsIgnoreCase(nodeName)) children[i].setText(newValue.toString());
	}
}

Void setNodeValue(XMLNode parent, String nodeName, Float newValue, Integer decLength) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (children[i].getName().equalsIgnoreCase(nodeName)) children[i].setText(newValue.toString(decLength));
	}
}

Void setNodeValue(XMLNode parent, String nodeName, Bool newValue) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (children[i].getName().equalsIgnoreCase(nodeName)) children[i].setText(newValue.toString());
	}
}

/*
        Node: Validations
 */

Bool nodeExists(XMLNode parent, String nodeName) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (children[i].getName().equalsIgnoreCase(nodeName)) return true;
	}
	return false;
}

Bool nodeValueExists(XMLNode parent, String nodeValue) {
	XMLNode[] children = parent.getChildren();
	for (Integer i = 0; i < children.length(); i++) {
		if (children[i].getText().equals(nodeValue)) return true;
	}
	return false;
}

Bool isComplexType(XMLNode node) {
	String type = node.getParameter("type");
	if (type.equals("array") || type.equals("object")) return true;
	return false;
}

Bool isEmpty(XMLNode node) {
 XMLNode[] props = node.getChildren();
 if (props.length() == 0) {
  if (!node.getText().isEmpty()) return false;
  return true;
 }
 return false;
}

/*
        Node: Mutations
 */

XMLNode stripNode(XMLNode source, XMLNode remove) {
	XMLNode target = ObjectNode(source.getName());
	XMLNode[] properties = source.getChildren();
	for (Integer i = 0; i < properties.length(); i++) {
		String propertyName = properties[i].getName();
		if (!nodeValueExists(remove, propertyName)) target.addChild(properties[i]);
	}
	return target;
}

/**************************** END NODE FUNCTIONS ******************************/

XMLNode PostData(XMLNode data) {
	XMLNode postData = ObjectNode("data");
	postData.addChild(data);
	return postData;
}

XMLNode PostData(XMLNode[] data) {
	XMLNode postData = ObjectNode("data");
	postData.setChildren(data);
	return postData;
}

XMLNode Criteria(String field, String operator, String value) {
	XMLNode crit = ObjectNode("criteria");
	crit.addChild(Node("field", field, "string"));
	crit.addChild(Node("operator", operator, "string"));
	crit.addChild(Node("value", value, "string"));
	return crit;
}

String getLoginSecret() {
	User user = getActiveUser();
	Integer associateId = user.getValue("associateId").toInteger();
	if (associateId == 0) return "";
	SearchEngine se;
	se.addField("Credentials.secret");
	se.addCriteria("Credentials.associateId", "equals", associateId.toString());
	se.setLimit(1);
	for (se.execute(); !se.eof(); se.next()) {
		return se.getField(0).urlEncode();
	}
	return "";
}

XMLNode getUDList(String listName, Integer listId, Integer languageId) {
	XMLNode array = ArrayNode(listName);
	NSMDOAgent mdoAgent;
	NSMDOListItem[] items = mdoAgent.GetList("udlist", true, listId.toString(), false);
	for (Integer i = 0; i < items.length(); i++) {
		XMLNode[] properties;
		properties.pushBack(Node("id", items[i].GetId()));
		properties.pushBack(Node("name", items[i].GetName().parseSOMultiLanguageString(languageId)));
		array.addChild(ObjectNode("item", properties));
	}
	return array;
}

NSEntityElement[] createEntityElements(String csv) {
	NSEntityElement[] elements;
	Vector vec;
	vec.parseString(csv, ",");
	for (Integer i = 0; i < vec.size(); i++) {
		String value = vec.get(i);
		NSEntityElement element;
		element.SetValue(value);
		elements.pushBack(element);
	}
	return elements;
}

Bool isOk(XMLNode response) {
	Integer statusCode = getNodeValue(response, "statusCode").toInteger();
	if (statusCode < 300) return true;
	return false;
}

Integer indexOf(String[] array, String predicate) {
	for (Integer i = 0; i < array.length(); i++) {
		Bool afterWildcard = array[i].endsWith("*");
		Bool beforeWildcard = array[i].beginsWith("*");
		String current = array[i].stripLeadingAndTrailing("*");
		if (beforeWildcard) {
			if (predicate.endsWith(current)) return i;
		} else if (afterWildcard) {
			if (predicate.beginsWith(current)) return i;
		} else {
			if (array[i].equals(predicate)) return i;
		}
	}
	return -1;
}

Integer getTableId(String tableName) {
	String table = "extra_tables";
	table += ".";
	SearchEngine se;
	se.addField("extra_tables.id");
	se.addCriteria("extra_tables.table_name", "equals", tableName);
	se.execute();
	for (se.execute(); !se.eof(); se.next()) {
		return se.getField(0).toInteger();
	}
	return 0;
}

String getTableName(Integer tableId) {
	String table = "extra_tables";
	table += ".";
	SearchEngine se;
	se.addField(table + "table_name");
	se.addCriteria(table + "id", "equals", tableId.toString());
	se.setLimit(1);
	se.execute();
	for (se.execute(); !se.eof(); se.next()) {
		return se.getField(0);
	}
	return "";
}

String[] getTableFields(Integer tableId) {
	String[] res;
	res.pushBack("id");
	String table = "extra_fields";
	table += ".";
	SearchEngine se;
	se.addField(table + "field_name");
	se.addCriteria(table + "extra_table", "equals", tableId.toString());
	se.addOrder(table + "order_pos", true);
	for (se.execute(); !se.eof(); se.next()) {
		res.pushBack(se.getField(table + "field_name"));
	}
	return res;
}

XMLNode getTableMeta(Integer tableId) {
	SearchEngine se;
	se.addField("extra_fields.field_name");
	se.addField("extra_fields.name");
	se.addField("extra_fields.type");
	se.addField("extra_fields.target_extra_table");
	se.addField("extra_fields.flags");
	se.addOrder("extra_fields.order_pos", true);
	se.addCriteria("extra_fields.extra_table", "equals", tableId.toString());
	XMLNode res = ObjectNode("meta");
	for (se.execute(); !se.eof(); se.next()) {
		XMLNode[] props;
		props.pushBack(Node("field_name", se.getField(0)));
		props.pushBack(Node("name", se.getField(1)));
		props.pushBack(Node("type", se.getField(2).toInteger()));
		if (!se.getField(3).isNull()) props.pushBack(Node("target_extra_table", se.getField(3).toInteger()));
		props.pushBack(Node("flags", se.getField(4).toInteger()));
		res.addChild(ObjectNode(se.getField(0).substitute("x_", ""), props));
	}
	return res;
}

XMLNode getTableData(Integer tableId) {
	String[] fields = getTableFields(tableId);
	String tableName = getTableName(tableId);
	SearchEngine se;
	for (Integer i = 0; i < fields.length(); i++) {
		se.addField(tableName + "." + fields[i]);
	}
	String res = se.executeJSON();
	while (res.find(tableName) > -1) {
		res = res.substitute(tableName + ".", "");
	}
	while (res.find("x_") > -1) {
		res = res.substitute("x_", "");
	}
	return parseJSON(res);
}

/*
   Author:     Lars Andreas Ness
   Date:       31.08.2016
   Filename:   "geas_httpmethods.ejs"

   Desc:       Library for HTTP-related methods. When using the SO Parser to run
              scripts, we control the output 100%. This allows us to determine
              the Content-Type header, as well as any other headers, which gives
              us the ability to emulate API endpoints.
 */

Map _headers =
	Map()
	.insert("Cache-Control", "no-cache, no-store, must-revalidate")
	.insert("Pragma", "no-cache")
	.insert("Expires", "0");

String getStatus(XMLNode response) {
	return getNodeValue(response, "statusCode") + ": " + getNodeValue(response, "statusText");
}

Void AddHttpHeader(String key, String value) {
	_headers.insert(key, value);
}

Void SetHttpStatus(String status) {
	_headers.insert("Status", status);

	if (!_headers.exists("Content-Type"))
		_headers.insert("Content-Type", "application/json;charset=utf-8");

	String h;
	for (_headers.first(); !_headers.eof(); _headers.next())
		h += _headers.getKey() + ": " + _headers.getVal() + "\n";

	setParserVariable("ej.headers", h);
}

/*
   [200] Result Methods
 */
XMLNode ResponseNode(Integer statusCode, String statusText, String context) {
	XMLNode[] props;
	props.pushBack(Node("statusText", statusText, "string"));
	props.pushBack(Node("statusCode", statusCode.toString(), "number"));
	props.pushBack(Node("context", context, "string"));
	return ObjectNode("response", props);
}

XMLNode Ok(String context) {
	Integer statusCode = 200;
	String statusText = "Ok";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", "Ok", "string"));
	return response;
}

XMLNode Ok(String message, String context) {
	XMLNode response = Ok(context);
	response.addChild(Node("message", message, "string"));
	return response;
}

XMLNode Ok(XMLNode data, String context) {
	XMLNode response = Ok(context);
	data.setName("results");
	response.addChild(data);
	return response;
}

XMLNode Ok(String message, XMLNode data, String context) {
	XMLNode response = Ok(message, context);
	data.setName("results");
	response.addChild(data);
	return response;
}

XMLNode Ok(String data, String context) {
	XMLNode response = Ok("Dynamic File Serving", context);
	response.addChild(Node("results", data, "string"));
	response.addChild(Node("raw", "true", "boolean"));
	return response;
}

XMLNode File(Attachment att, String context) {
	XMLNode response = Ok("File", context);
	att.dump();
	response.addChild(Node("file", "true", "boolean"));
	return response;
}

XMLNode Redirect(String location, String context) {
	XMLNode response = ResponseNode(200, "Redirect", context);
	response.addChild(Node("context", context, "string"));
	response.addChild(Node("message", "Omdirigerer. Vennligst vent..", "string"));
	AddHttpHeader("Location", location);
	return response;
}

/*
   [400] Result Methods
 */
XMLNode BadRequest(String context) {
	Integer statusCode = 400;
	String statusText = "Bad Request";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", "Bad Request", "string"));
	return response;
}
XMLNode BadRequest(String message, String context) {
	Integer statusCode = 400;
	String statusText = "Bad Request";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", message, "string"));
	return response;
}

XMLNode NotFound(String context) {
	Integer statusCode = 404;
	String statusText = "Not Found";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", "Not Found", "string"));
	return response;
}
XMLNode NotFound(String message, String context) {
	Integer statusCode = 404;
	String statusText = "Not Found";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", message, "string"));
	return response;
}

XMLNode MethodNotAllowed(String context) {
	Integer statusCode = 405;
	String statusText = "Method Not Allowed";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", "Method Not Allowed", "string"));
	return response;
}
XMLNode MethodNotAllowed(String message, String context) {
	Integer statusCode = 405;
	String statusText = "Method Not Allowed";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", message, "string"));
	return response;
}

XMLNode ExpectationFailed(String context) {
	Integer statusCode = 417;
	String statusText = "Expectation Failed";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", "Expectation Failed", "string"));
	return response;
}
XMLNode ExpectationFailed(String message, String context) {
	Integer statusCode = 417;
	String statusText = "Expectation Failed";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", message, "string"));
	return response;
}

XMLNode NotAcceptable(String context) {
	Integer statusCode = 406;
	String statusText = "Not Acceptable";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", "Not Acceptable", "string"));
	return response;
}
XMLNode NotAcceptable(String message, String context) {
	Integer statusCode = 406;
	String statusText = "Not Acceptable";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", message, "string"));
	return response;
}

/*
   [500] Result Methods
 */
XMLNode GenericError(Integer statusCode, String statusText, String message, String context) {
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", message, "string"));
	Log(context, response.toJSON(0));
	return response;
}

XMLNode InternalServerError(String context) {
	Integer statusCode = 500;
	String statusText = "Internal Server Error";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	return response;
}
XMLNode InternalServerError(String message, String context) {
	Integer statusCode = 500;
	String statusText = "Internal Server Error";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", message, "string"));
	return response;
}
XMLNode NotImplemented(String context) {
	Integer statusCode = 501;
	String statusText = "Not Implemented";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	return response;
}
XMLNode NotImplemented(String message, String context) {
	Integer statusCode = 501;
	String statusText = "Not Implemented";
	XMLNode response = ResponseNode(statusCode, statusText, context);
	response.addChild(Node("message", message, "string"));
	return response;
}

/*
   End methods
 */

XMLNode HttpRequest(Map opts, Map queryParams, XMLNode data) {
	String CTX = Context("httpmethods", "HttpRequest");
	String url = opts.get("url");
	String method = opts.get("method");
	if (url.isEmpty())
		return NotAcceptable("Option property [url] cannot be empty", CTX);
	if (method.isEmpty())
		return NotAcceptable("Option property [method] cannot be empty", CTX);

	for (queryParams.first(); !queryParams.eof(); queryParams.next()) {
	  String key = queryParams.getKey();
	  String value = queryParams.getVal();
		url += "&" + key + "=" + value;
	}
	HTTP http;
	XMLNode[] dataProps = data.getChildren();
	for (Integer i = 0; i < dataProps.length(); i++) {
		XMLNode prop = dataProps[i];
		String key = prop.getName();
		String value = prop.getText();
		if (isComplexType(prop))
			value = prop.toJSON(0);
		http.setValue(key, value);
	}
	String response = "";
	if (method == "GET") {
		response = String(http.get(url));
	} else if (method == "POST") {
		response = String(http.post(url));
	} else if (method == "DELETE") {
		response = String(http.delete(url));
	} else if (method == "PUT") {
		response = String(http.put(url));
	}
	response = response.utf8Decode();
	Log(CTX + " - Response", response);

	if (http.hasError()) {
		return BadRequest(http.getErrorMessage(), CTX);
	}
	return parseJSON(response);
}

Void Response(XMLNode response, Bool isInternalRequest) {
	String status = getStatus(response);
	if (status.isEmpty()) status = "200 OK";
	SetHttpStatus(status);
	Bool isFileResponse = getNodeValue(response, "file").toBool();
	if (isInternalRequest) {
		print(response.toJSON(0));
	} else {
		if (isFileResponse) {
			// The file has already been dumped with the necessary headers.
			// - ref. geas_httpmethods.File()
			return;
		} else {
			// Ignore the context surrounding the response.
			// TODO: Response message? Indications?
			XMLNode results = getNode(response, "results");
			if (isEmpty(results))
				results = getNode(response, "message");
			if (isEmpty(results)) {
				return;
			} else {
				print(results.toJSON(0));
			}
		}
	}
}
