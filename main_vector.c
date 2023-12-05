#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


//Program, który pozwoli użytkownikowi na wykonywanie podstawowych operacji na wektorze.
//Do tego przygotowałem strukturę vector_t, która będzie działała jak wektor w c++.
//Program, pobiera od użytkownika liczbę elementów, na jaką ma zostać zarezerwowana pamięć na tablicę.
//
//W przypadku kiedy alokacja pamięci się nie powiedzie program wyswietla komunikat Failed to allocate memory i kończy działanie z kodem błędu 8.
//W przypadku podania błędnych danych program  wyświetla komunikat Incorrect input i kończy działanie z kodem błędu 1.
//W przypadku podania błędnej liczby elementów komunikat Incorrect input data i kończy działanie z kodem błędu 2.
//Następnie program pyta się użytkownika, co ten chce zrobić:
//
//0 - Zakończyć działanie.
//1 - Dodać elementy do tablicy.
//2 - Usunąć elementy z tablicy.
//Dodawanie: Program prosi użytkownika o podanie wartości kolejnych elementów i dodaje je do tablicy. Pobieranie trwa do podania przez użytkownika 0 lub do momentu niepowodzenia zwiększenia przydzielonej pamięci, na co reaguje komunikatem Failed to allocate memory.
//
//Usuwanie: Program prosi użytkownika o podanie wartości kolejnych elementów i usuwa je z tablicy.
//
//W przypadku podania opcji o wartości innej niż dopuszczalna, program wyświetla komunikat Incorrect input data i kontynuuje działanie.
//W przypadku podania błędnych danych program wyświetla komunikat Incorrect input i niezwłocznie kończy działanie z kodem błędu 1.
//Po zakończeniu operacji dodawania/usuwania program wyświetla zawartość tablicy. Jeśli ta jest pusta, to wyswietla komunikat Buffer is empty. Następnie program kontynuuje swoje działanie, aż do wybrania opcji 0.

int main() {


    int size;
    printf("Podaj rozmiar tablicy");
    if(scanf("%d", &size) != 1){
        printf("Incorrect input");
        return 1;
    }
    //sdf
    if(size <= 0){
        printf("Incorrect input data");
        return 2;
    }

    struct vector_t array;
    int check = vector_create(&array,size);
    if(check == 2){
        printf("Failed to allocate memory");
        vector_destroy(&array);
        return 8;
    }

    int element;
    int count = 0;
    int decyzja;
    while (1){
        printf("Podaj co chcesz zroibc\n");
        if(scanf("%d", &decyzja) != 1){
            vector_destroy(&array);
            printf("Incorrect input");
            return 1;
        }

        if(decyzja == 0)
            break;

        else if(decyzja == 1){
            printf("Podaj kolejne liczby, ktore maja zostac dodane do tablicy:\n");
            while (1){

                if(scanf("%d", &element) != 1){
                    printf("Incorrect input");
                    vector_destroy(&array);
                    return 1;
                }

                if(element == 0)
                    break;

                if(vector_push_back(&array,element)==2){
                    printf("Failed to allocate memory\n");

                    break;
                }
                count++;


            }
            if(count == 0){
                printf("Buffer is empty");
            }
            else
            {
                vector_display(&array);
                while (getchar() != '\n'){}
            }

        }

        else if(decyzja == 2){
            printf("Podaj kolejne liczby, ktore maja zostac usuniete:\n");
            while (1){
                if(scanf("%d", &element) != 1){
                    printf("Incorrect input");
                    vector_destroy(&array);
                    return 1;
                }


                int c = vector_erase(&array,element);
                count-=c;

                if(count <= 0){
                    printf("Buffer is empty\n");
                    break;
                }

                if(element == 0)
                    break;
            }
            vector_display(&array);
            while (getchar() != '\n'){}


        }
        else{
            printf("Incorrect input data\n");
        }
    }

    vector_destroy(&array);
    vector_create_struct(NULL,10);
    vector_destroy_struct(NULL);
    return 0;
}
