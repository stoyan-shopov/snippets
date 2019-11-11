#include <stdio.h>

// Tested on a 32 bit machine, pointers are 32 bit (four bytes) in size

// In the C language, a data object of an 'array of x' type is implicitly converted in expressions to a
// data object of type 'a pointer to x', with two exceptions:
// when the data object of an 'array' type is an operand of the ampersand (&), or the 'sizeof' operator
int main(void)
{

	// Expected: 12 - exceptional handling of arrays versus pointers.
	// An array is not converted to a pointer in the case of being an operand to an 'ampersand',
	// or a 'sizeof' operator (this case).
	// The type in this case remains an array: so there are 11 bytes in the string + 1 byte for the null terminator - 12 bytes in total
	printf("Line %i: %i, expected 12\n", __LINE__, sizeof "Test string");
	// Expected: 12. Same as above, the dereference (*) and 'address-of' (ampersand, &) operators cancel each other
	printf("Line %i: %i, expected 12\n", __LINE__, sizeof * & "Test string");
	// Expected 11: 12 byte for the character array, minus 1
	printf("Line %i: %i, expected 11\n", __LINE__, sizeof "Test string" - 1);
	// Expected: 4. Pointer arithmetic - the size of a pointer to a 'char' (which is four bytes), minus 1 - yields a pointer, which is 4 bytes in size
	printf("Line %i: %i, expected 4\n", __LINE__, sizeof("Test string" - 1));
	// Expected: 4. The size of a pointer (to whatever, in this case - an array), is 4 bytes in size
	printf("Line %i: %i, expected 4\n", __LINE__, sizeof & "Test string");	
	// Expected: 1. Dereference, the type pointed to by a 'pointer to char' is 'char', which is 1 byte in size
	printf("Line %i: %i, expected 1\n", __LINE__, sizeof * "Test string");	
	// Expected: 5. The size of a pointer, which is 4 bytes in size, plus one
	printf("Line %i: %i, expected 5\n", __LINE__, sizeof & "Test string" + 1);
	// Expected: 4. Address arithmetic - the result is the number of elements between the two pointers of the same type (pointers to 'char'),
	// which is of type 'size_t', which is 4 bytes in size on a 32 bit machine
	printf("Line %i: %i, expected 4\n", __LINE__, sizeof("Test string" - "another Test string"));

	// Expected: 1. The size of an element of an 'array of char' type, which is a 'char' - 1 byte in size
	printf("Line %i: %i, expected 1\n", __LINE__, sizeof "Test string"[2]);
	// Expected: 4. The size of a pointer to an element of a 'char' array, which is a pointer to a 'char' - 4 bytes in size, as any other pointer on a 32 bit machine
	printf("Line %i: %i, expected 4\n", __LINE__, sizeof & "Test string"[2]);

	// Expected: 12 - exceptional handling of arrays versus pointers.
	// The "test array" string literal is an operand to the ampersand(&) operator, so it is not
	// converted to type 'pointer to char' - instead, it remains of type 'array of 12 chars', so the
	// type of the expression '& "Test string"' is effectively a 'pointer to an array of 12 chars'.
	// Subscripting a 'pointer to an array of 12 chars' (in this case with index 2), yields
	// a data object of type 'array of 12 chars', which is 12 bytes in size
	printf("Line %i: %i, expected 12\n", __LINE__, sizeof (& "Test string")[2]);
	// Expected: 12 - exceptional handling of arrays versus pointers.
	// Same as above, the array subscript operator('[]') in C is commutative,
	// that is 'ptr[2]' is equivalent to '2[ptr]'
	printf("Line %i: %i, expected 12\n", __LINE__, sizeof 2[& "Test string"]);
	// Expected: 12 - exceptional handling of arrays versus pointers.
	// Same as above, but uses the pointer dereference('*') and address arithmetic,
	// instead of the array subscript('[]') operator
	printf("Line %i: %i, expected 12\n", __LINE__, sizeof * (2 + & "Test string"));

	return 0;
}
