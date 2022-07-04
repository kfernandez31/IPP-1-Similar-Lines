/** @file
  Interfejs dynamicznej tablicy w C inspirowanej wektorem z C++

  @authors Kacper Kramarz-Fernandez <k.kramarzfer@student.uw.edu.pl>
  @copyright Uniwersytet Warszawski
  @date 2021
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>
#include <stdbool.h>

/**
 * Domyślny początkowy rozmiar wektora.
 */
#define INIT_CAP 1

/**
 * Zwraca i-ty element wektora z castem na oczekiwany typ @p TYPE.
 *
 * @param[in] TYPE : typ, na który castujemy
 * @param[in] vector : wektor
 * @param[in] index : indeks
 *
 * @return : wskaźnik na i-ty element po zcastowaniu
 */
#define GET_ITEM(TYPE,vector,index) (TYPE*)VectorAt(vector, index)

/**
 * Umieszcza nowy element w wektorze, i zakańcza program, jeśli to niemożliwe.
 *
 * @param[in] vect : wektor
 * @param[in] el : umieszczany element
 *
 * @return : wskaźnik na i-ty element
 */
#define SAFE_PUSH(vect, el) \
do{                             \
    if (VectorPush(vect, el) != VECT_OK) {\
        fprintf(stderr, "ERROR during pushback\n");\
        exit(EXIT_FAILURE);         \
    }                               \
}while(0)

/**
 * Struktura reprezentująca wektor.
 */
typedef struct vector_t {
	void *items;         ///< Dane przechowywane w wektorze
	size_t obj_size;     ///< Rozmiar instancji danych z wektora (w bajtach)
    size_t cap;          ///< Pojemność (w ilości elementów)
	size_t size;         ///< Zajęte miejsce (w ilości elementów)
} vector_t;

/**
 * Kody stanu zwracane przez niektóre funkcje.
 */
typedef enum vect_errcode_t {
    VECT_OK = 0,         ///< Sukces
    VECT_ERR = -1,       ///< Generyczny błąd
    VECT_ENOMEM = -2,    ///< Brak pamięci
} vect_errcode_t;

/**
 * Tworzy nową instancję wektora.
 * @param[in] obj_size : rozmiar każdego elementu w bajtach
 * @param[in] cap : początkowa pojemność wektora
 * @return : nowy wektor
 */
vector_t *VectorNew(size_t obj_size, size_t cap);

/**
 * Destruktor dla dynamicznie zaalokowanego wektora.
 * @param[in] v : wektor
 */
void VectorDestroy(vector_t *v);

/**
 * Zwraca wskaźnik do @p i -tego elementu @p v.
 * @param[in] v : wektor
 * @param[in] i : indeks
 * @return : wskaźnik na i-ty element lub NULL w przypadku za dużego indeksu.
 */
void *VectorAt(vector_t *v, size_t i);

/**
 * Ścina pojemność wektora do ilości jego zajętych elementów (v->size).
 * @param[in] v : wektor
 */
vect_errcode_t VectorShrinkToFit(vector_t *v);

/**
 * Dodaje nie-NULL-owy obiekt (@p item) niezawarty w wektorze
 * @p v na jego koniec.
 * @param[in] v : wektor
 * @param[in] item : dodawany obiekt
 */
vect_errcode_t VectorPush(vector_t *v, const void *item);


#endif //__VECTOR_H__