#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 10
#define COLS 15
#define SHOWS 4

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define BOLD "\033[1m"

struct Booking {
    int bookingID;
    char name[50];
    int showID;
    int seatCount;
    char seats[10][5];
    int ticketCost;
    int snackCost;
    int totalAmount;
};

int seats[SHOWS][ROWS][COLS] = {0};
int bookingCounter = 1;

// Menu
void printMenu() {
    printf(CYAN "\n========================================\n" RESET);
    printf(BOLD "        MOVIE BOOKING SYSTEM\n" RESET);
    printf(CYAN "========================================\n" RESET);
    printf(CYAN "1. View Shows\n" RESET);
    printf(CYAN "2. View Seat Layout\n" RESET);
    printf(CYAN "3. Book Tickets\n" RESET);
    printf(CYAN "4. View Booking\n" RESET);
    printf(CYAN "5. Cancel Booking (Refund)\n" RESET);
    printf(CYAN "6. Occupancy Report\n" RESET);
    printf(CYAN "7. Exit\n" RESET);
    printf(CYAN "========================================\n" RESET);
}

// Shows
void displayShows() {
    printf("\n1. Leo - 10:00 AM");
    printf("\n2. Jailer - 1:00 PM");
    printf("\n3. Vikram - 4:00 PM");
    printf("\n4. Master - 7:00 PM\n");
}

// Seats
void displaySeats(int showID) {
    if(showID < 1 || showID > SHOWS) {
        printf(RED "Invalid show choice!\n" RESET);
        return;
    }
    printf(CYAN "\nSeat Layout for Show %d (O=Available X=Booked)\n\n" RESET, showID);
    printf("    ");
    for(int j=0;j<COLS;j++) printf("%3d",j+1);
    printf("\n");
    for(int i=0;i<ROWS;i++) {
        printf("%c  ", 'A'+i);
        for(int j=0;j<COLS;j++) {
            if(seats[showID-1][i][j]==0) printf(CYAN " O " RESET);
            else printf(RED " X " RESET);
        }
        printf("\n");
    }
}

// Snacks
int selectSnacks() {
    int choice, qty, total = 0;
    printf("\nSelect Snacks & Drinks:\n");
    printf("1. Popcorn (Rs.100)\n2. Coke (Rs.50)\n3. Combo (Popcorn + Coke) (Rs.130)\n4. Skip\n");
    while(1) {
        printf("Enter choice: ");
        scanf("%d",&choice);
        if(choice==4) return total;
        if(choice<1 || choice>4) { printf(RED "Invalid choice\n" RESET); continue; }
        printf("Enter quantity: ");
        scanf("%d",&qty);
        if(qty<=0) { printf(RED "Invalid quantity\n" RESET); continue; }
        switch(choice) {
            case 1: total += qty*100; break;
            case 2: total += qty*50; break;
            case 3: total += qty*130; break;
        }
        printf(GREEN "Added successfully!\n" RESET);
        return total;
    }
}

// Save
void saveBooking(struct Booking b) {
    FILE *fp = fopen("bookings.txt","a");
    fprintf(fp,"%d %s %d %d %d %d %d\n",
            b.bookingID,b.name,b.showID,b.seatCount,
            b.ticketCost,b.snackCost,b.totalAmount);
    fclose(fp);
}

// Receipt
void printReceipt(struct Booking b) {
    printf(CYAN "\n================================\n" RESET);
    printf(BOLD "          MOVIE RECEIPT\n" RESET);
    printf(CYAN "================================\n" RESET);
    printf("Booking ID : %d\nCustomer   : %s\nShow       : %d\n",b.bookingID,b.name,b.showID);
    printf("Seats      : ");
    for(int i=0;i<b.seatCount;i++) printf("%s ",b.seats[i]);
    printf("\nTickets    : Rs.%d\nSnacks     : Rs.%d\nTotal Cost : Rs.%d\n",b.ticketCost,b.snackCost,b.totalAmount);
    printf(CYAN "================================\n" RESET);
}

// Book
void bookTicket() {
    struct Booking b;
    b.bookingID = bookingCounter++;
    printf("Enter name: ");
    scanf("%s",b.name);
    displayShows();
    printf("Select show (1-4): ");
    scanf("%d",&b.showID);
    if(b.showID < 1 || b.showID > SHOWS) {
        printf(RED "Invalid show choice!\n" RESET);
        return;
    }
    printf("Number of seats: ");
    scanf("%d",&b.seatCount);
    if(b.seatCount <= 0 || b.seatCount > 10) {
        printf(RED "Invalid seat count!\n" RESET);
        return;
    }
    for(int i=0;i<b.seatCount;i++) {
        char rowChar; int col;
        printf("Enter seat (Example A 5): ");
        scanf(" %c %d",&rowChar,&col);
        int row = rowChar - 'A'; col--;
        if(row<0 || row>=ROWS || col<0 || col>=COLS) { printf(RED "Invalid seat!\n" RESET); i--; continue; }
        if(seats[b.showID-1][row][col]==1) { printf(RED "Already booked!\n" RESET); i--; continue; }
        seats[b.showID-1][row][col] = 1;
        sprintf(b.seats[i], "%c%d", rowChar, col+1);
    }
    b.ticketCost = b.seatCount * 150;
    b.snackCost = selectSnacks();
    b.totalAmount = b.ticketCost + b.snackCost;
    printf(GREEN "\nBooking Successful!\n" RESET);
    printReceipt(b);
    saveBooking(b);
}

// View
void viewBooking() {
    FILE *fp = fopen("bookings.txt","r");
    if(!fp) { printf(RED "No bookings found\n" RESET); return; }
    struct Booking b; int id;
    printf("Enter Booking ID: ");
    scanf("%d",&id);
    while(fscanf(fp,"%d %s %d %d %d %d %d",
                 &b.bookingID,&b.name,&b.showID,&b.seatCount,
                 &b.ticketCost,&b.snackCost,&b.totalAmount)!=EOF) {
        if(b.bookingID==id) { printReceipt(b); fclose(fp); return; }
    }
    printf("Booking not found\n");
    fclose(fp);
}

// Cancel
void cancelBooking() {
    int id; printf("Enter Booking ID to cancel: ");
    scanf("%d",&id);
    FILE *fp = fopen("bookings.txt","r");
    if(!fp) { printf(RED "No bookings file found\n" RESET); return; }
    FILE *temp = fopen("temp.txt","w");
    struct Booking b; int found = 0;
    while(fscanf(fp,"%d %s %d %d %d %d %d",
                 &b.bookingID,&b.name,&b.showID,&b.seatCount,
                 &b.ticketCost,&b.snackCost,&b.totalAmount)!=EOF) {
        if(b.bookingID==id) {
            found = 1;
            printf(GREEN "Booking Cancelled! Refund: Rs.%d\n" RESET,b.totalAmount);
        } else {
            fprintf(temp,"%d %s %d %d %d %d %d\n",
                    b.bookingID,b.name,b.showID,b.seatCount,
                    b.ticketCost,b.snackCost,b.totalAmount);
        }
    }
    fclose(fp); fclose(temp);
    remove("bookings.txt"); rename("temp.txt","bookings.txt");
    if(!found) printf(RED "Booking ID not found\n" RESET);
}

// Report
void occupancy() {
    for(int s=0;s<SHOWS;s++) {
        int booked=0;
        for(int i=0;i<ROWS;i++) for(int j=0;j<COLS;j++) if(seats[s][i][j]==1) booked++;
        int total = ROWS*COLS;
        printf(CYAN "\nShow %d Occupancy:\n" RESET, s+1);
        printf("Total Seats: %d\nBooked Seats: %d\nAvailable Seats: %d\nOccupancy: %.2f%%\n",
               total,booked,total-booked,(booked*100.0)/total);
    }
}

// Main
// Main
int main() {
    int choice;
    printf(BOLD CYAN "\nWelcome to Movie Booking System\n" RESET);
    while(1) {
        printMenu();
        printf("Enter choice: ");
        if(scanf("%d",&choice)!=1) {
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            // clear input buffer
            while(getchar()!='\n');
            continue;
        }
        switch(choice) {
            case 1: 
                displayShows(); 
                break;
            case 2: {
                int showID;
                displayShows();
                printf("Select show (1-4): ");
                scanf("%d",&showID);
                displaySeats(showID);
                break;
            }
            case 3: 
                bookTicket(); 
                break;
            case 4: 
                viewBooking(); 
                break;
            case 5: 
                cancelBooking(); 
                break;
            case 6: 
                occupancy(); 
                break;
            case 7: 
                printf(GREEN "Thank you!\n" RESET); 
                exit(0);
            default: 
                printf(RED "Invalid choice! Please select between 1 and 7.\n" RESET);
        }
    }
}


