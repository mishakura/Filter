#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int blue = 0;
    int green = 0;
    int red = 0;
    float sum = 0;
    int final = 0;
    

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;
            sum = ((float)blue+green+red) / 3;
            final = round(sum);
            image[i][j].rgbtBlue = final;
            image[i][j].rgbtGreen = final;
            image[i][j].rgbtRed = final;
            blue = green = red = sum = final = 0;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int blue = 0;
    int green = 0;
    int red = 0;
   double sepiaBlue = 0;
   double sepiaGreen = 0;
   double sepiaRed = 0;
   int finalBlue = 0;
   int finalGreen = 0;
   int finalRed = 0;

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           blue = image[i][j].rgbtBlue;
           green = image[i][j].rgbtGreen;
           red = image[i][j].rgbtRed;
           sepiaBlue = (0.272 * (float)red) + (0.534 * (float)green) + (0.131 * (float)blue);
           sepiaGreen = (0.349 * (float)red) + (0.686 * (float)green) + (0.168 * (float)blue);
           sepiaRed = (0.393 * (float)red) + (0.769 * (float)green) + (0.189 * (float)blue);

           finalBlue = round(sepiaBlue);
           finalGreen = round(sepiaGreen);
           finalRed = round(sepiaRed);

           if(finalBlue > 255)
           {
               finalBlue = 255;
           }
           if(finalGreen > 255)
           {
               finalGreen = 255;
           }
           if(finalRed > 255)
           {
               finalRed = 255;
           }

           image[i][j].rgbtBlue = finalBlue;
           image[i][j].rgbtGreen = finalGreen;
           image[i][j].rgbtRed = finalRed;

           blue = green = red = sepiaBlue = sepiaGreen = sepiaRed = finalBlue = finalGreen = finalRed = 0;

        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int countdown = width;
    int blue = 0;
    int red = 0;
    int green = 0;
    
    for(int i = 0; i < height; i++)
    {
        countdown = width;

        if(width % 2 != 0)
        {
            for(int j = 0; j < (round((float)width/2) - 1); j++)
            {
              blue = image[i][j].rgbtBlue;
              green = image[i][j].rgbtGreen;
               red = image[i][j].rgbtRed;

              image[i][j].rgbtBlue = image[i][countdown - 1].rgbtBlue;
              image[i][j].rgbtGreen = image[i][countdown - 1].rgbtGreen;
              image[i][j].rgbtRed = image[i][countdown - 1].rgbtRed;

              image[i][countdown - 1].rgbtBlue = blue;
              image[i][countdown - 1].rgbtGreen = green;
              image[i][countdown - 1].rgbtRed = red;

           blue = red = green = 0;
                countdown--;

            }

        }
       else if(width % 2 == 0)
       {
           for(int k = 0; k < (width/2) ; k++)
           {
               blue = image[i][k].rgbtBlue;
               green = image[i][k].rgbtGreen;
               red = image[i][k].rgbtRed;

              image[i][k].rgbtBlue = image[i][countdown - 1].rgbtBlue;
              image[i][k].rgbtGreen = image[i][countdown - 1].rgbtGreen;
              image[i][k].rgbtRed = image[i][countdown - 1].rgbtRed;

              image[i][countdown - 1].rgbtBlue = blue;
              image[i][countdown - 1].rgbtGreen = green;
              image[i][countdown - 1].rgbtRed = red;

            blue = 0;
            green = 0;
            red = 0;

                countdown--;

           }
       }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE final[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
        double red = 0;
        double blue = 0;
        double green = 0;
        int finalRed = 0;
        int finalGreen = 0;
        int finalBlue = 0;
        int counter = 0;
         // Top 2x2.
           if(i == 0 && j == 0)
           {
                int updateJ = j;
                int updateI = i - 1;
               for(int c = 0; c < 2; c++)
               {
                   updateJ = j;
                   updateI++;
                   for(int r = 0; r < 2; r++)
                   {
                      blue += image[updateI][updateJ].rgbtBlue;
                      green += image[updateI][updateJ].rgbtGreen;
                      red  += image[updateI][updateJ].rgbtRed;
                      updateJ++;
                      counter++;
                   }
               }
           }
          // Top Middle 2x3.
           else if(i == 0 && j > 0 && j < width - 1)
           {
                int updateJ = j;
                int updateI = i - 1;
               for(int c = 0; c < 2; c++)
               {
                   updateJ = j - 1;
                   updateI++;
                   for(int r = 0; r < 3; r++)
                   {
                      blue += image[updateI][updateJ].rgbtBlue;
                      green += image[updateI][updateJ].rgbtGreen;
                      red += image[updateI][updateJ].rgbtRed;
                       updateJ++;
                       counter++;
                   }
               }
           }
        // Top last column
        else if(i == 0 && j == width - 1)
        {
            int updateJ = j;
            int updateI = i - 1;
            for(int c = 0; c < 2; c++)
               {
                   updateJ= j;
                   updateI++;
                   for(int r = 0; r < 2; r++)
                   {
                      blue += image[updateI][updateJ-1].rgbtBlue;
                      green +=image[updateI][updateJ-1].rgbtGreen;
                      red += image[updateI][updateJ-1].rgbtRed;
                      updateJ++;
                      counter++;
                   }
               }
        }
         // Middle middle 3x3.
         else if(i > 0 && i < height - 1 && j > 0 && j < width - 1)
         {
             int updateJ = j;
             int updateI = i - 2;
               for(int c = 0; c < 3; c++)
               {
                   updateJ = j;
                   updateI++;
                   for(int r = 0; r < 3; r++)
                   {
                      blue += image[updateI][updateJ-1].rgbtBlue;
                      green += image[updateI][updateJ-1].rgbtGreen;
                      red +=  image[updateI][updateJ-1].rgbtRed;
                      updateJ++;
                      counter++;
                   }
               }
        }
        // Bottom 2x2
        else if(i == height - 1 && j == 0)
        {
                int updateJ = j;
                int updateI = i + 1;

               for(int c = 0; c < 2; c++)
               {
                   updateJ = j;
                   updateI--;
                   for(int r = 0; r < 2; r++)
                   {
                      blue += image[updateI][updateJ].rgbtBlue;
                      green +=image[updateI][updateJ].rgbtGreen;
                      red += image[updateI][updateJ].rgbtRed;
                      updateJ++;
                      counter++;
                   }
               }
        }
        // Bottom middle 2x3
        else if(i == height - 1 && j > 0 && j < width - 1)
        {
               int updateJ = j;
                int updateI = i + 1;
               for(int c = 0; c < 2; c++)
               {
                   updateJ = j - 1;
                   updateI--;
                   for(int r = 0; r < 3; r++)
                   {
                      blue += image[updateI][updateJ].rgbtBlue;
                      green +=image[updateI][updateJ].rgbtGreen;
                      red += image[updateI][updateJ].rgbtRed;
                       updateJ++;
                       counter++;
                   }
               }

        }
        // Last bottom 2x2.
        else if(i == height - 1 && j == width - 1)
        {
             int updateJ = j;
                int updateI = i + 1;

               for(int c = 0; c < 2; c++)
               {
                   updateJ = j;
                   updateI--;
                   for(int r = 0; r < 2; r++)
                   {
                      blue += image[updateI][updateJ-1].rgbtBlue;
                      green += image[updateI][updateJ-1].rgbtGreen;
                      red += image[updateI][updateJ-1].rgbtRed;
                      updateJ++;
                      counter++;
                   }
               }
        }
        // Special case.
        else if (i > 0 && i < height - 1 && j == 0)
        {
                int updateJ = j;
                int updateI = i - 2;

               for(int c = 0; c < 3; c++)
               {
                   updateJ = j;
                   updateI++;
                   for(int r = 0; r < 2; r++)
                   {
                      blue += image[updateI][updateJ].rgbtBlue;
                      green += image[updateI][updateJ].rgbtGreen;
                      red += image[updateI][updateJ].rgbtRed;
                      updateJ++;
                      counter++;
                   }
               }
        }
       // Special case 2.
       else if(j == width - 1 && i > 0 && i < height - 1)
       {
            int updateJ = j;
            int updateI = i - 2;
               for(int c = 0; c < 3; c++)
               {
                   updateJ = j;
                   updateI++;
                   for(int r = 0; r < 2; r++)
                   {
                      blue += image[updateI][updateJ-1].rgbtBlue;
                      green += image[updateI][updateJ-1].rgbtGreen;
                      red += image[updateI][updateJ-1].rgbtRed;
                      updateJ++;
                      counter++;
                   }
               }
       }
            // Doing the average and copying them into an array.
            finalBlue = round(blue/counter);
            finalGreen = round(green/counter);
            finalRed = round(red/counter);
            final[i][j].rgbtBlue = finalBlue;
            final[i][j].rgbtGreen = finalGreen;
            final[i][j].rgbtRed =   finalRed;
    }
    }
      // Copy array values to real bmp.
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = final[i][j].rgbtBlue;
            image[i][j].rgbtGreen = final[i][j].rgbtGreen;
            image[i][j].rgbtRed  =  final[i][j].rgbtRed;
        }
    }

   
    return;
}
