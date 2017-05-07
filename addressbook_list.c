#include "addressbook_list.h"

/**
* Note this file is *NOT* to contain console output,
* meaning printf's are *NOT* to be present in this file.
*/

AddressBookList * createAddressBookList()
{
    /**
    * Allocates and initialises a new AddressBookList.
    * malloc or calloc are expected to be used to create the
    * AddressBookList memory.
    * 
    * If memory cannot be allocated for the list NULL is returned.
    * 
    * Note head, tail and current should all be initialised to NULL.
    */

	AddressBookList * list = malloc(sizeof(*list));
	if(list != NULL) {/* malloc might return null */
		list->size = 0;
		list->head = list->tail = list->current = NULL;
	}

	return list;

}

void freeAllNodes(AddressBookList *list) {
	list->current = list->tail;

	while(list->current != list->head) {
		list->current = list->current->previousNode;
		freeAddressBookNode(list->current);
	}
	freeAddressBookNode(list->head);
}

void freeAddressBookList(AddressBookList * list)
{
    /**
     * Free's all nodes within the list and the AddressBookList itself.
     * 
     * Note the freeAddressBookNode(...) function is used to free a node.
     */

	freeAllNodes(list);
	free(list);

}

AddressBookNode * createAddressBookNode(int id, char * name)
{
    /**
    * Allocates and initialises a new AddressBookNode.
    * malloc or calloc are expected to be used to create the
    * AddressBookNode memory.
    * 
    * Note the array of the node should also be created and initialised,
    * which should be done with the createAddressBookArray(...) function.
    * 
    * If memory cannot be allocated for the node or array NULL is returned.
    * 
    * Note previousNode and nextNode should both be initialised to NULL.
    */

	AddressBookNode * node = malloc(sizeof(*node));
	if( node != NULL) {/* malloc might return null */
		node->id = id;
		strcpy(node->name, name);
		node->array = createAddressBookArray();
		node->previousNode = node->nextNode = NULL;
		return node;
	}

    return NULL;
}

void freeAddressBookNode(AddressBookNode * node)
{
    /**
    * Free's the array within the node and the AddressBookNode itself.
    * 
    * Note the freeAddressBookArray(...) function is used to free the array.
    */
	freeAddressBookArray(node->array);
	/*free(node->id);
	free(node->name);*/
	node->previousNode = NULL;
	node->nextNode = NULL;
	free(node);
}

Boolean insertNode(AddressBookList * list, AddressBookNode * node)
{
    /**
     * Inserts the node into the list and returns TRUE.
     * 
     * If the list already contains a node with the same id
     * then FALSE is returned and the node is not inserted.
     */

	/*inserts at tail*/
	if(list->head == NULL) {
		/* empty list */
		list->head = list->tail = list->current = node;
	} else {
		/* normal operation */
		list->tail->nextNode = node;
		node->previousNode = list->tail;
		list->tail = node;
	}
	list->size++;

    return FALSE;
}

Boolean deleteCurrentNode(AddressBookList * list)
{
    /**
     * Delete's and free's the current node in the list and returns TRUE.
     * 
     * Note the freeAddressBookNode(...) function is used to free a node.
     * 
     * If the list has no nodes (i.e., there is no current node)
     * then FALSE is returned.
     */
    
    return FALSE;
}

Boolean forward(AddressBookList * list, int forward)
{
    /**
     * Moves the current node forward in the list by the number provided
     * and returns TRUE.
     * 
     * If the current node cannot be moved forward by that many positions
     * then FALSE is returned and current remains unchanged.
     */
	int i;
	AddressBookNode * current = list->current;

	for(i = 0; i < forward; i++) {
		if(current->nextNode != NULL) {
			current = current->nextNode;
		} else {
			return FALSE;
		}
	}
	list->current = current;
    return TRUE;
}

Boolean backward(AddressBookList * list, int backward)
{
    /**
    * Moves the current node backward in the list by the number provided
    * and returns TRUE.
    * 
    * If the current node cannot be moved backward by that many positions
    * then FALSE is returned and current remains unchanged.
    */
	int i;
	AddressBookNode * current = list->current;

	for(i = 0; i < backward; i++) {
		if(current->previousNode != NULL) {
			current = current->previousNode;
		} else {
			return FALSE;
		}
	}
	list->current = current;
    return TRUE;
}

AddressBookNode * findByID(AddressBookList * list, int id)
{
    /**
     * Returns the node that matches the id provided.
     * 
     * If no node with a matching id exists then NULL is returned.
     */
	AddressBookNode * node = list->head;

	while(node->id != id && node != NULL) {
		node = node->nextNode;
	}
	return node;

}

AddressBookNode * findByName(AddressBookList * list, char * name)
{
    /**
    * Sets current to the first node that matches the name provided
    * and returns this node.
    * 
    * If no node with a matching name exists then NULL is returned
    * and current remains unchanged.
    */

	AddressBookNode * node = list->head;

	while(node->name != name && node != NULL) {
		node = node->nextNode;
	}
	return node;

}
