/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <cs50.h>
 #include <string.h>
 #include <stdlib.h>
 #include<stdint.h>
 
 
 typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", "card.raw" );
        return 2;
    }
    
    BYTE index = -1;
    BYTE buffer[513];
    char* title = "-01.jpg";
    
    FILE* outptr = fopen("-01.jpg", "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", title);
        return 3;
    }
    
    //Finds the first instance of jpeg
    while(!feof(inptr))
    {
       fread(&buffer, sizeof(BYTE), 1, inptr);
       if(buffer[0] == 0xff)
       {
         fread(&buffer, sizeof(BYTE), 3, inptr);
         if(buffer[0] == 0xd8 && buffer[1] == 0xff && (buffer[2] == 0xe1 || buffer[2] == 0xe0))
         {
           fseek(inptr, -4*sizeof(BYTE), SEEK_CUR);           
           break;
         }  
       }
    }
    
    
    while(fread(&buffer, sizeof(BYTE), 512, inptr) ==512 )
    {
        
                
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe1 || buffer[3] == 0xe0))
        {
          //Open new file and close existing file, if any
          if(index != 0)
          {                        
             //Close existing file
             fclose(outptr);                        
          }
          else
             fclose(outptr);
          
          index++;
          char *title = malloc(8);
            
          sprintf(title, "%03d.jpg", index);
            
          //Open the new fle
          outptr = fopen(title, "w");
          if (outptr == NULL)
          {
              fclose(inptr);
              fprintf(stderr, "Could not create %s.\n", title);
              return 3;
          }  
          free(title);                                          
        }
         
       //Write onto the file
       fwrite(&buffer, sizeof(BYTE), 512, outptr);   
       
                
    }
    
    remove("-01.jpg");
    fclose(outptr);
    fclose(inptr);
}
