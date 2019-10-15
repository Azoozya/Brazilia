#include "header.h"

mp* create_master_pointer(void)
{
  mp* to_return;
  do {
     to_return = malloc(sizeof(mp));
  } while(test_succes(to_return) != YES);
  to_return->next = NULL;
  to_return->previous = NULL;
  to_return->pointer = to_return;
  return to_return;
}

int add_pointer_master(void* pointer,mp* master)
{
  mp* buffer = reach_last_cell_mp(master);
  int counter = 0;
  do {
     buffer->next = malloc(sizeof(mp));
     counter++;
  } while(test_succes(buffer->next) != YES && counter < MAX_TRY);

  if (counter  == MAX_TRY || buffer->next == NULL)
    {
      printf("Ajout du pointeur impossible.\n");
      return NO;
    }
  else
    {
      buffer->next->previous = buffer;
      buffer->next->next = NULL;
      buffer->next->pointer = pointer;
      return YES;
    }
}

// void* reach_last_cell(void* head)
// {
//   mp* to_return = head;
//   printf("[RLC]%p\n",to_return->next);
//   while(to_return->next != NULL)
//     {
//       to_return = to_return->next;
//     }
//   return (void*)to_return;
// }

objet* reach_last_cell_obj(objet* head)
{
  objet* to_return = head;

  if (test_succes(head) == YES)
  {
    while(to_return->next != NULL)
      {
        to_return = to_return->next;
      }
  }

  return to_return;
}

mp* reach_last_cell_mp(mp* head)
{
  mp* to_return = head;

  if (test_succes(head) == YES)
  {
    while(to_return->next != NULL)
      {
        to_return = to_return->next;
      }
  }

  return to_return;
}

//Libère chacune des cellules d'une liste chaînée en partant de la tête, la structure doit avoir un pointeur next.
void delete_down(mp* head)
{
  mp* buffer;
  int counter = 0;
  do
    {
      buffer = head->next;
      if(head->pointer != head)
        free(head->pointer);
      free(head);
      head = buffer;
      counter ++;
    }
    while (head != NULL);
  printf("Suppression de %d cellules effectué\n",counter);
}
