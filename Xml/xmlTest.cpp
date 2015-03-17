#include <stdio.h>  
#include <libxml/parser.h>  
#include <libxml/tree.h>  

void parseDoc(char *filename);  
void printChildrenNames(xmlDocPtr doc, xmlNodePtr cur);  

//解析xml文件  
void parseDoc(char *filename) {  

	xmlDocPtr doc;  
	xmlNodePtr cur;  

	xmlKeepBlanksDefault(0);  
	//解析文档  
	doc = xmlParseFile(filename);  

	if (doc == NULL ) {  
		fprintf(stderr,"Document not parsed successfully.\n");  
		return;  
	}  

	//获取根结点  
	cur = xmlDocGetRootElement(doc);  
	if (cur == NULL) {  
		fprintf(stderr,"empty document\n");  
		xmlFreeDoc(doc);  
		return;  
	}  
	//输出根结点信息  
	printf("root node=%s\n", cur->name);  
/*
	if (cur == NULL) {  
		fprintf(stderr,"empty document\n");  
		xmlFreeDoc(doc);  
		return;  
	}  
*/
	//打印子结点信息  
	printChildrenNames(doc, cur);  

	xmlFreeDoc(doc);  
	return;  
}  

//打印子结点信息  
void printChildrenNames(xmlDocPtr doc, xmlNodePtr cur) {  
	xmlChar *key;  
	xmlChar* attr_value;  
	if (cur != NULL) {  
		cur = cur->xmlChildrenNode;  

		while (cur != NULL){  
			//如果是元素结点，则输出其名称和内容  
			if(cur->type == XML_ELEMENT_NODE){  
				printf("Current Node: %s\t\t", cur->name);  
				//获取结点内容  
				key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);  
				if(key != NULL)  
					printf("content: %s\t\t", key);  
				xmlFree(key);  
				//获取结点属性，data为属性名  
				attr_value = xmlGetProp(cur, (const xmlChar *)"data");  
				if(attr_value != NULL)  
					printf("data: %s",attr_value);  
				xmlFree(attr_value);  
				printf("\n");  
			}  
			printChildrenNames(doc, cur);  
			cur = cur->next;  
		}  

		return;  
	}else{  
		fprintf(stderr, "ERROR: Null Node!");  
		return;  
	}  
}  

int main(int argc, char **argv) {  
	/*
	if (argc != 2) {  
		printf("Parameter too litter!\n");  
		return(1);  
	} 
	*/

	/* 
	 * this initialize the library and check potential ABI mismatches 
	 * between the version it was compiled for and the actual shared 
	 * library used. 
	 */  
	LIBXML_TEST_VERSION  

	parseDoc("./test.xml");  
	//parseDoc(argv[1]);  

	/* 
	 * Cleanup function for the XML library 
	 */  
	xmlCleanupParser();  
	/* 
	 * this is to debug memory for regression tests 
	 */  
	xmlMemoryDump();  
	return(0);  
}  
