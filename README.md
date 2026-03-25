# Movie Ticket Booking System

An efficient C-based mini project to manage movie ticket bookings for a single theatre.  
This project was developed as part of a digital assignment.

---

## Problem Statement
Managing movie ticket bookings manually often leads to errors and double bookings.  
This system provides a digital solution where users can:
- View available shows
- Check seat layout
- Book tickets with seat validation
- Add snacks to their order
- Generate receipts
- Cancel bookings with refunds
- View occupancy reports

---

## Features Implemented
- View available movies/shows  
- Display seat layout (O = available, X = booked)  
- Book tickets (with seat validation and snack selection)  
- Prevent double booking of seats  
- Generate booking receipt (Booking ID, customer name, show, seats, total amount)  
- Store bookings in file (`bookings.txt`)  
- View booking by Booking ID  
- Cancel booking with refund  
- Occupancy report per show (total seats, booked seats, available seats, occupancy %)  
- Input validation and error handling  

---

## System Design
### Structure Definition
```c
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



Functions
printMenu() → displays main menu

displayShows() → shows available movies

displaySeats() → prints seat layout

bookTicket() → books tickets and snacks

viewBooking() → views booking by ID

cancelBooking() → cancels booking and refunds

occupancy() → generates occupancy report

saveBooking() → saves booking to file

printReceipt() → prints formatted receipt

selectSnacks() → handles snack selection

File Handling
File name: bookings.txt

Format: text file (space-separated values)

Example record:

Code
1001 Arun 1 2 300 100 400
Program Flow
Menu-driven interface

Booking validates seat availability and prevents duplicates

Searching retrieves booking by ID from file

Cancellation rewrites file excluding cancelled booking

Reports calculate occupancy percentage per show

Core Logic
Seat booking validation (row/column bounds, duplicate check)

Ticket cost = seat count × fixed price (₹150)

Snack cost based on menu selection and quantity

Total amount = ticket cost + snack cost

File storage ensures persistence of bookings

Occupancy report = (booked ÷ total seats) × 100

Testing and Validation
Normal case: booking seats successfully

Invalid input: wrong seat number rejected

Boundary case: maximum 10 seats per booking

Duplicate seat: prevented with error message

File not found: handled gracefully

Cancel booking: refunds and removes record

Deployment
Uploaded project files to GitHub repository

Enabled GitHub Pages for documentation hosting

Used Replit for live demo since C cannot run directly on GitHub Pages

Issues faced: file path handling and missing README (resolved with relative paths and adding README.md)

Challenges Faced
Handling seat validation and preventing double booking

File handling for cancellation (using temporary file)

Debugging input validation for snacks and menu choices

Learned structured programming, file I/O, and error handling in C

AI Usage Declaration
Used AI for structuring documentation and debugging logic explanations

Modified wording and added features manually

Debugging of file handling and seat validation done independently

Author
Name: Dhananjai

GitHub Repository: MovieTicketBookingSystem

Conclusion
This mini project helped in understanding C programming concepts such as structures, arrays, functions, file handling, and input validation.
It provided practical experience in building a real-world application with modular design and persistent storage.