#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100

// RecordType
struct RecordType
{
    int		id;
    char	name;
    int		order;
};

struct HashNode
{
    struct RecordType record;
    struct HashNode* next;
};

// Fill out this structure
struct HashType
{
    struct Node* head;
};

// Compute the hash function
int hash(int x)
{
 return x % TABLE_SIZE;
}

void insertRecord(struct HashType* pHashArray, struct RecordType record)
{
    int index = hash(record.id);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->record = record;
    newNode->next = NULL;

    if (pHashArray[index].head == NULL)
    {
        pHashArray[index].head = newNode;
    }
    else
    {
        struct HashNode* currentNode = pHashArray[index].head;
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}


// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    for (i = 0; i < hashSz; ++i)
    {
        if (pHashArray[i].head != NULL)
        {
            printf("Index %d -> ", i);
            struct HashNode* currentNode = pHashArray[i].head;
            while (currentNode != NULL)
            {
                printf("%d, %c, %d -> ", currentNode->record.id, currentNode->record.name, currentNode->record.order);
                currentNode = currentNode->next;
            }
            printf("NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Your hash implementation
    struct HashType hashTable[TABLE_SIZE];
    int i;
    for (i = 0; i < TABLE_SIZE; ++i)
    {
        hashTable[i].head = NULL;
    }

    // Insert
    for (i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, pRecords[i]);
    }
    displayRecordsInHash(hashTable, TABLE_SIZE);

    return 0;



}