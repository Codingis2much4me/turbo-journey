#include <stdio.h>
#include<stdbool.h>

bool str_copy(char source[], char dest[]);
bool is_suffix(char str[], char suf[]);
bool is_substring(char str[], char substr[]);
bool get_suffix(char str[], char suf[], int len);
bool get_substring(char str[], int start, int len);
int size_array(char a[]);
bool is_same(char first[], char second[]);
void concatenate(char source1[], char source2[]);
void convert_to_upper(char str[]);

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
    printf("%d\n", is_suffix(template_array, suf));
    
    printf("Calling is_substring on input:\n");
    fgets(template_array, 150, stdin);
    printf("Enter the sequence to be checked as substring:\n");
    char substr[150];
    fgets(substr, 150, stdin);
    printf("%d", is_substring(template_array, substr));
    
    printf("Calling get_suffix on input:\n");
    fgets(template_array, 150, stdin);
    printf("Enter the length to be extracted:\n");
    int len;
    scanf(" %d", &len);
    char suf2[len];
    printf("\n%d", get_suffix(template_array, suf2, len));
    
    printf("Calling get_substring on input/source:\n");
    getchar();
    fgets(template_array, 150, stdin);
    printf("Enter the starting position of the substring:\n");
    int start_letter;
    scanf("%d", &start_letter);
    printf("Enter the length to be extracted:\n");
    scanf("%d", &len);
    printf("\n%d", get_substring(template_array, start_letter, len));
    
    printf("Calling is_same on input 1:\n");
    char inp1[150];
    getchar();
    fgets(inp1, 150, stdin);
    printf("input 2:\n");
    char inp2[150];
    fgets(inp2, 150, stdin);
    printf("%d\n", is_same(inp1, inp2));
    
    printf("Calling convert_to_upper on input:\n");
    fgets(inp1, 150, stdin);
    convert_to_upper(inp1);
    
    printf("Calling concatenate on input 1:\n");
    fgets(inp1, 150, stdin);
    printf("Input 2:\n");
    fgets(inp2, 150, stdin);
    concatenate(inp1, inp2);
    
    
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
            for(int j = i; j < size_array(str); j++)
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
    int i;
    
    for(i = 0; i < len; i++)
    {
        suf[i] = str[size_array(str) - len - 1 + i];
    }
    suf[i] = '\0';
    printf("%s\n", suf);
    
    if(size_array(suf) == len)
        return true;
    else 
        return false;
}

bool get_substring(char str[], int start, int len)
{
    char substr[len];
    int counter = 0;
    
    for(int i = start - 1; i < start - 1 + len; i++)
    {
        substr[counter++] = str[i];
    }
    substr[counter] = '\0';
    if(counter == len)
    {
        printf("%s", substr);
        return true;
    }
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

void concatenate(char source1[], char source2[])
{
    char dest[size_array(source1) + size_array(source2) - 2];
    int i, j;
    
    for( i = 0; i < size_array(source1); i++)
    {
        if(source1[i] != '\0' && source1[i] != '\n')
        dest[i] = source1[i];
    }
    for(j = 0; j < size_array(source2); j++)
    {
        if(source2[j] != '\0')
        dest[i+j] = source2[j];
    }
    dest[i+j] = '\0';
    printf("%s", dest);
}

void convert_to_upper(char str[])
{
    char uppercase;
    for(int i = 0; i < size_array(str); i++)
    {
        if(str[i] >= 97 && str[i] <= 123)
        {
            uppercase = str[i] - 32;
            str[i] = uppercase;
        }
    }
    printf("%s", str);
}

