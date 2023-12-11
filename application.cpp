#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
void parseXmlFile(const char *filename) {
xmlDocPtr doc;
xmlNodePtr currNode;
// Parse the file
doc = xmlReadFile(filename, NULL, 0);
if (doc == NULL) {
fprintf(stderr, "Failed to parse %s\n", filename);
return;
}
// Get the root element
currNode = xmlDocGetRootElement(doc);
// Traverse the XML tree
while (currNode != NULL) {
// Check if the node is an element
if (currNode->type == XML_ELEMENT_NODE) {
// Check if the element is "book"
// Ensure that the root element is not NULL
if (currNode != NULL && xmlStrcmp(currNode->name, (const xmlChar *)"catalog") == 0) {
// Iterate through the child nodes of the catalog element
xmlNodePtr bookNode = currNode->xmlChildrenNode;
while (bookNode != NULL) {
// Check if the node is an element and is "book"
if (bookNode->type == XML_ELEMENT_NODE && xmlStrcmp(bookNode->name, (const xmlChar
*)"book") == 0) {
char* title = NULL;
printf("Found 'book' element\n");
// Iterate through the child nodes of the book element
xmlNodePtr bookChildNode = bookNode->xmlChildrenNode;
while (bookChildNode != NULL) {
// Check if the child node is an element and is "title"
if (bookChildNode->type == XML_ELEMENT_NODE &&
xmlStrcmp(bookChildNode->name, (const xmlChar *)"title") == 0) {
// Get the content of the title element
xmlChar *titleContent = xmlNodeListGetString(doc, bookChildNode->xmlChildrenNode, 1);
title = (char*)titleContent; // Convert to C string
break; // We found the title, no need to continue
}
// Move to the next child node
bookChildNode = bookChildNode->next;
}
// Print the title if found
if (title != NULL) {
printf("Book Title: %s\n", title);
}
}
// Move to the next sibling node (next book element)
bookNode = bookNode->next;
}
} else {
fprintf(stderr, "Root element is not 'catalog'\n");
}
}
// Move to the next sibling node
currNode = currNode->next;
}
// Free the XML document
xmlFreeDoc(doc);
}
int main() {
const char *filename = "catalog.xml";
parseXmlFile(filename);
return 0;
}
