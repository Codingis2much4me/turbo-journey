#include <stdio.h>
#include<stdbool.h>

bool str_copy(char source[], char dest[]);
bool is_suffix(char str[], char suf[]);
bool is_substring(char str[], char substr[]);
bool get_suffix(char str[], char suf[], int len);
bool get_substring(char str[], char substr[], int start, int len);
int size_array(char a[]);

int main()
{
    char template_array[150];
    printf("Calling str_copy on input/source\n");
    fgets(template_array, 150, stdin);
    char dest[150];
    str_copy(template_array, dest);
    
    printf("Calling is_suffix on input: \n");
    fgets(template_array, 150, stdin);
    printf("Enter the sequence to be checked as suffix:\n");
    char suf[150];
    fgets(suf, 150, stdin);
    printf("%s%s", suf, template_array);
    printf("%d", is_suffix(template_array, suf));
    
    printf("Calling is_substring on input:\n");
    fgets(template_array, 150, stdin);
    printf("Enter the sequence to be checked as substring:\n");
    char substr[150];
    fgets(substr, 150, stdin);
    printf("%d", is_substring(template_array, substr));
    
    
    
}

int size_array(char a[])
{
    int i;
    for(i = 0;;i++)
    {
        if(a[i] != '\0')
            continue;
        else
            break;
    }
    return i;
}

bool str_copy(char source[], char dest[])
{
    int i;
    for ( i = 0; i < size_array(source); i++)
    {
        dest[i] = source[i];
        
    }
    if(i == size_array(source))
    {
        printf("%s", dest);
        return true;
    }
    else 
        return false;
}

bool is_suffix(char str[], char suf[])
{
    int counter = 0;
    
    for(int i = size_array(str) - size_array(suf); i < size_array(str); i ++)   
    { //Loop will start from 
        
        if(str[i] == suf[counter])
            counter++;
        else
            return false;
    }
    
    return true;
}

bool is_substring(char str[], char substr[])
{
    for(int i = 0; i < size_array(str); i++)
    {
        if (str[i] == substr[0])
        {
            int count = 0;
            for(int j = i; j < size_array(substr); j++)
            {
                if(str[j] == substr[count++])
                {
                    continue;
                }
                else 
                    break;
            }
            if(count == size_array(substr))
                return true;
            
        }
    }
    return false;
}

bool get_suffix(char str[], char suf[], int len)
{
    for(int i = 0; i < len; i++)
    {
        suf[i] = str[i];
        printf("%c\t", suf[i]);
    }
    printf("\n");
    if(size_array(suf) == len)
        return true;
    else 
        return false;
}

bool get_substring(char str[], char substr[], int start, int len)
{
    int counter = 0;
    
    for(int i = start - 1; i < start - 1 + len; i++)
    {
        substr[counter++] = str[i];
    }
    if(size_array(substr) == len)
        return true;
    return false;
}

bool is_same(char first[], char second[])
{
    for(int i = 0; i < size_array(first); i++)
    {
        if(first[i] != second[i] || size_array(first) != size_array(second))
            return false;
    }
    return true;
}

void concatenate(char source1[], char source2[], char dest[])
{
    int i;
    for( i = 0; i < size_array(source1); i++)
    {
        dest[i] = source1[i];
    }
    for(int j = 0; j < size_array(source2); j++)
    {
        dest[i+j] = source2[j];
    }
    printf("%s", dest);
}

