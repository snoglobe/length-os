#include "paging.h"

uint32_t page_directory[1024] __attribute__((aligned(4096)));

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

void init_paging()
{
    term_print("paging1");
    for(int i = 0; i < 1024; i++)
    {
        page_directory[i] = 0x00000002;
    } 
    term_print("paging2");
    uint32_t page_table[1024] __attribute__((aligned(4096)));;
    for(unsigned int i = 0; i < 1024; i++)
    {
        page_table[i] = (i * 0x1000) | 3;
    }
    term_print("paging3");
    loadPageDirectory(page_directory);
    term_print("paging4");
    enablePaging();
}

void* requestPage()
{
    int emptyPage;
    for(int i = 0; i < 1024; i++)
    {
        if(page_directory[i] == 0x00000002)
        {
            emptyPage = i;
        }
    }
    uint32_t page[1024] __attribute__((aligned(4096)));
    for(unsigned int i = 0; i < 1024; i++)
    {
        page[i] = (i * 0x1000) | 3;
    }
    page_directory[emptyPage] = ((unsigned int)page) | 3;
    return (void*)page_directory[emptyPage];
}