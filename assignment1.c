/*-----------------------------------------------------------
 * Programmer--Bryan Crawley
 * Course------CS 4223
 * Project-----Homework #1
 * Due---------September 1, 2017
 *
 * This program computes and displays an estimated square
 * root.
 *-----------------------------------------------------------
 */

#include <stdio.h>

int main() {
    float x; /* The number whose square root is estimated */
    float estimate; /* Estimated square root */
    float newEstimate; /* Closer estimated square root */
    float difference; /* Difference between estimates */
    
    /* Enter the raw data. */
    printf("Select number: ");
    scanf("%f",&x);
    
    /* An initial estimate of the square root */
    newEstimate = 1;
    
    /* Estimate the square root */
    do {
        estimate = newEstimate;
        newEstimate = 0.5*(estimate + x/estimate);
        difference = newEstimate - estimate;
    } while ((difference < -0.005) || (difference > 0.005));
    
    /* Display the estimated square root */
    printf("Approximate square root: %e\n", newEstimate);
    
    return 0;
}
