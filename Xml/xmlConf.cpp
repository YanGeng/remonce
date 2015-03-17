#include "xmlConf.h"
#include <assert.h>
#include "macro.h"
#include <iostream>

// Construct
XmlConf::XmlConf() : xmlDepth(0)
	,xmlDepthLimit(2) {
}

XmlConf::XmlConf(int depth, int depthLimit) : xmlDepth(depth)
	,xmlDepthLimit(depthLimit) {
}


/********************************************************************************
 * func_name:	setXmlDepthLimit
 * return:		void
 * parameters:	depthLimit : int
 * description: return the limit valaue of the xmlDepth
 * *****************************************************************************/
void XmlConf::setXmlDepthLimit(int depthLimit) {
	xmlDepthLimit = depthLimit;
}


/********************************************************************************
 * func_name:	getXmlDepthLimit
 * return:		int
 * parameters:	void
 * description: return the value of the xmlDepthLimit
 * *****************************************************************************/
int XmlConf::getXmlDepthLimit() const {
	return xmlDepthLimit;
}


/********************************************************************************
 * func_name:	readXmlConf 
 * return:		true : if sucess; else false
 * parameters:	fileName : const char *
 * description: read the xml config-file, store the value to a map url2Service
 *				, at last return this map
 * *****************************************************************************/
bool XmlConf::readXmlConf(const char *fileName) {
	assert(fileName);

	xmlDocPtr doc;
	xmlNodePtr cur;

#ifdef _DEBUG 
    CURRENT_FILE_LINE;
#endif 

	xmlKeepBlanksDefault(0);
	// analyze the xml file
	doc = xmlParseFile(fileName);

	if (doc == NULL ) {
		//fprintf(stderr,"Document not parsed successfully.\n");
		std::cout << "Document not parsed successfully.\n";
		return false;
	}

	// get the root node of the xml
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		std::cout << "empty document\n";
		xmlFreeDoc(doc);
		return false;
	}  
	// get the value of the root node 
	std::string rootValue = reinterpret_cast<const char*>(cur->name);
	if (rootValue.compare("web-app") != 0) {
		std::cout << "The xml file is not web conf-file or there are errors in the conf-file\n";
		return false;
	}

	// read the children node
	bool returnFlag = readChildrenNode(doc, cur);

	xmlFreeDoc(doc);
	
	return returnFlag;
}


/********************************************************************************
 * func_name:	readChildrenNode 
 * return:		bool: true when sucess else false
 * parameters:	doc : xmlDocPtr; cur : xmlNodePtr
 * description: This function is used to read the children node of the xml file
 *				, and will store the relationship between url and service to the
 *				map: url2Service
 * *****************************************************************************/
bool XmlConf::readChildrenNode(xmlDocPtr doc, xmlNodePtr cur) {
	if (!doc || !cur) 
		return false;

	xmlDepth++;
	if (xmlDepth > xmlDepthLimit) {
		xmlDepth--;
		return true;
	}

#ifdef _DEBUG 
    CURRENT_FILE_LINE;
#endif 

	xmlChar *key = NULL;  
	xmlChar* attr_value = NULL;  
	if (cur != NULL) {
		cur = cur->xmlChildrenNode;  
		std::string mapKey;
		std::string mapValue;

		while (cur != NULL) {  
			// if it's element node, get its value
			if(cur->type == XML_ELEMENT_NODE){  
				// printf("Current Node: %s\t\t", cur->name);  
				std::string curNode = reinterpret_cast<const char*>(cur->name);
				if (xmlDepth == 1 && curNode.compare("servlet") == 0) {
					std::cout << "Find the servlet node\n";
				} else if (xmlDepth == 2) {
					// get the content of the node
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);  
					if(key != NULL) { 
						//printf("content: %s\t\t", key);
						if (curNode.compare("servlet-name") == 0) {
							mapValue = std::string(reinterpret_cast<const char*>(key));
						} else if (curNode.compare("url-pattern") == 0) {
							mapKey = std::string(reinterpret_cast<const char*>(key));
						}
						xmlFree(key);  
					}
					// 获取结点属性，data为属性名  
					attr_value = xmlGetProp(cur, (const xmlChar *)"data");  
					if(attr_value != NULL)  
						std::cout << "data: " << attr_value << std::endl;  
					xmlFree(attr_value);  
				} else {
					xmlDepth--;
					return true;
				}
			} 
			// Read the children node of current node
			readChildrenNode(doc, cur);
			cur = cur->next;  
			if (xmlDepth == 2 && cur == NULL) {
				url2Service[mapKey] = mapValue;
				mapKey.clear();
				mapValue.clear();
			}
		}
		xmlDepth--;
		return true;
	} else {
		std::cout << "ERROR: Null Node!\n";
		xmlDepth--;
		return false;
	} 
}


/********************************************************************************
 * func_name:	getXmlConf
 * return:		std::map<std::string, std::string>
 * parameters: 
 * description: return the url2Service
 * *****************************************************************************/
std::map<std::string, std::string> XmlConf::getXmlConf() const {
	return url2Service;
}
