# Programming Assignments

---

## Assignment 1

1. **Find Largest Number**  
   Write a program to input five numbers and find the largest one using only the if-else ladder.

2. **Convert Years**  
   Write a program to convert a user-input number of years into months, days, hours, minutes, and seconds using a switch-case statement.

3. **Display Stars**  
   Write a program to display any number of stars on the screen. Provide a menu with the following options:
   - **1**: Fullscreen
   - **2**: Half screen
   - **3**: Top 3 lines
   - **4**: Bottom 3 lines
   - **5**: Right-angled triangle (right angle at bottom right)
   - **6**: Isosceles triangle (base at the bottom)
   - **7**: Circle (as shown in the lab)
   - **8**: Diamond blank (as shown in the lab)

---

## Assignment 2

1. **Sum of Squares (LSD = 5)**  
   Write a program to calculate the sum of the squares of numbers whose least significant digit is five, between two user-input numbers. Print the numbers, their squares, and the sum.

2. **Decimal Conversion**  
   Write a program to convert a decimal number to:

   - A. Binary
   - B. Octal
   - C. Hexadecimal  
     Use a CASE statement.

3. **Hydroelectric Dam Power Calculation**  
   Write a program to assist in designing a hydroelectric dam. Prompt for the dam's height and water flow (cubic meters per second). Predict megawatts produced if 90% of gravitational work is converted to electrical energy.  
   Report outputs for:
   - A. Height = 200 m, Flow = 1.50 × 10³ m³/s
   - B. Height = 170 m, Flow = 1.30 × 10³ m³/s

---

## Assignment 3

1. **Call by Value vs Reference**  
   Write a program to illustrate the difference between call by value and call by reference using two separate functions.

2. **Arithmetic on Fractions**  
   Write a program to perform arithmetic operations (add, subtract, multiply, divide) on common fractions, displaying results in reduced form.  
   Use these function prototypes:
   ```c
   void scan_fraction(int *nump, int *denomp);
   char get_operator(void);
   void add_fractions(int n1, int d1, int n2, int d2, int *n_ansp, int *d_ansp);
   void multiply_fraction(int n1, int d1, int n2, int d2, int *n_ansp, int *d_ansp);
   int find_gcd(int n1, int n2);
   void reduce_fraction(int *nump, int *denomp);
   void print_fraction(int num, int denom);
   ```

---

## Assignment 4

1. **Array Elements & Addresses**  
   Display array elements with their addresses using the array name as a pointer.

2. **Sum of Array Elements**  
   Find the sum of array elements using the array name as a pointer.

3. **Array of Pointers**  
   Store addresses of different array elements using an array of pointers.

4. **Function Address**  
   Display the address of a user-defined function.

5. **Call main() via Pointer**  
   Call `main()` using a pointer to the main function.

6. **Trim Blanks**  
   Complete `trim_blanks` to remove leading/trailing blanks from a string using `strncpy`.

7. **String Comparison (Case-Insensitive)**  
   Complete `string_greater` to find out-of-order elements when alphabetizing strings, ignoring case. Write `string_toupper` to convert strings to uppercase before comparison.

---

## Assignment 5

1. **String Length (With/Without Spaces)**  
   Find the length of a string including and excluding spaces using pointers.  
   Output format:

   ```
   Length of the string including spaces: xxx
   Length of the string excluding spaces: yyy
   ```

2. **Compare Two Strings**  
   Read two strings, compare character by character, display similar characters, and count dissimilar ones.  
   Output format:

   ```
   Similar characters found in both strings are as follows.
   <characters>
   The strings are different at **_ places.
   The string characters are similar at _** places.
   ```

3. **Compare Three Characters**  
   Enter three characters using pointers. Use `memcmp()` to compare. If all are the same, display "the characters are same"; otherwise, indicate their order or status alphabetically.

4. **Print String Up to Character**  
   Read a string and print it up to the first occurrence of a user-entered character.

5. **Sort Names and Ages**  
   Store names (last name first) and ages in parallel arrays. Sort names alphabetically, keeping ages with correct names.  
   Sample output:

   ```
   ## Original list
   Tendulkar, Sachin 42
   Ganguly, Sourav 44
   Richards, Vivian 58

   ## Alphabetized list
   Ganguly, Sourav 44
   Richards, Vivian 58
   Tendulkar, Sachin 42
   ```

---

## Assignment 6

1. **Display File with Line Numbers**  
   Read a file and display its contents with line numbers.

2. **Find File Size**  
   Find the size of a text file without traversing it character by character.

3. **Append File Contents**  
   Add the contents of one file to the end of another.

4. **Copy File (Uppercase Conversion)**  
   Copy one file to another,
