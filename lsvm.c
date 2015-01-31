/*
 
 lsvm  - list virtual machines

 A simple program to read through the xml created from registered virtual machines, parse the list
and read through the relevant .vmx files and list the virtual machine names.
 
Compile with the following line:
 gcc -Wall -o lsvm -std=c99 $(xml2-config --cflags) $(xml2-config --libs) lsvm.c
 
Written by Daniel Finneran 31/01/15
                                   
 */

#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>

char *parseStringForChar(char *string, char searchChar)
{
    /* return string between delimiter search Char*/
    int start = 0, charPos = 0; /*dont start the search*/
    size_t stringLength = strlen(string);
    char foundString[stringLength];
    for (size_t i = 0; i < stringLength; i++)
    {
        if (string[i] == searchChar) {
            start++;
        } else if (start == 2) {
            /*second sighting*/
            break;
            //i = stringLength;
        } else if (start == 1) {
            foundString[charPos] = string[i];
            charPos++;
        }
    }
    return strndup(foundString, charPos);
}

int main(int argc, char **argv)
{
    xmlDoc         *document;
    xmlNode        *root, *first_child, *second_child, *node;
    char           *filename = "/etc/vmware/hostd/vmInventory.xml";
    FILE           *fp;
    char           buffer[1024];   

    
    document = xmlReadFile(filename, NULL, 0);
    root = xmlDocGetRootElement(document);
    first_child = root->children;
    for (node = first_child; node; node = node->next) {
        if (node->type == 1) {
            second_child = node->children->next->next->next->children; // hideous xml path to the XML content
            if (second_child->type == 3) { /* replace 3 with the constant/definition */
                /*
                 - Dont print file path yet
                 */
                const char *filePath = (const char *)second_child->content; /* Casting here from an xmlChar * */
                fp = fopen(filePath, "r");
                if (fp) { /*file opened succesfully */
                    while(! feof(fp)){
                        fgets(buffer, 1024, fp);
                        /* Do stuff */
                        
                        if (strstr(buffer, "displayName")) /*Not Working, string comparrison was the incorrect way around*/
                        {
                            printf("%s \n", parseStringForChar(buffer, '"'));

                        }
                    }
                    
                fclose(fp);
                } else {
                    printf("Error opening file %s \n", filePath);
                }
            }
        }
    }
    return 0;
}


