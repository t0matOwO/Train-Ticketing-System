#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;


class Route {
public:
    Route(const string& name, const string& departure, const string& arrival, int distance)
        : name(name), departure(departure), arrival(arrival), distance(distance)
    {}
    string getName() const { return name; }
    string getDeparture() const { return departure; }
    string getArrival() const { return arrival; }
    int getDistance() const { return distance; }

private:
    string name;
    string departure;
    string arrival;
    int distance;
};

class Train {
public:
    Train(const string& trainNumber, const Route& route, const string& schedule, int totalSeats)
        : trainNumber(trainNumber), route(route), schedule(schedule), totalSeats(totalSeats)
    {
        seats.reserve(totalSeats);
        for (int i = 1; i <= totalSeats; ++i) {
            seats.push_back(false);
        }
    }

    string getSchedule() const { return schedule; }

    bool reserveSeat(int seatNumber)
    {
        if (seatNumber >= 1 && seatNumber <= totalSeats
            && !seats[seatNumber - 1]) {
            seats[seatNumber - 1] = true;
            return true;
        }
        return false;
    }

    int getTotalSeats() const { return totalSeats; }

    bool cancelSeat(int seatNumber)
    {
        if (seatNumber >= 1 && seatNumber <= totalSeats
            && seats[seatNumber - 1]) {
            seats[seatNumber - 1] = false;
            return true;
        }
        return false;
    }

    void displayTrainInfo() const
    {
        cout << "\n\t\t\tTrain Number: " << trainNumber << endl;
        cout << "\t\tRoute: " << route.getName() << " (" << route.getDeparture() << " to "
             << route.getArrival() << ")\n";
        cout << "\t\t\tDistance: " << route.getDistance() << " km" << endl;
        cout << "\t\t\tSchedule: " << schedule << endl;
        cout << "\t\t\tTotal Seats: " << totalSeats << endl;
        cout << "\t\t----- Availabe Seat -----\n";
        bool flag = false;
        for (int i = 0; i < totalSeats; i++) {
            if (!seats[i]) {
                cout << "\t\t" << i + 1;
            }
            else {
                cout << "\t\tNA";
            }
            if (!flag) {
                cout << "\t";
                flag = true;
            }
            else {
                cout << "\n";
                flag = false;
            }
        }
        cout << endl;
    }

    void displayAvailableSeats() const
    {
        cout << "\t\t\tAvailable Seats on Train " << trainNumber << ":\n";
        for (int i = 0; i < totalSeats; ++i) {
            if (seats[i]) {
                cout << "\t\t\tSeat " << i + 1 << ": Available\n";
            }
        }
    }

    void displayTrainStatus() const
    {
        int reservedSeats = 0;
        for (int i = 0; i < totalSeats; ++i) {
            if (seats[i]) {
                reservedSeats++;
            }
        }

        cout << "Train Status for Train " << trainNumber << ":\n";
        cout << "Total Seats: " << totalSeats << "\n";
        cout << "Reserved Seats: " << reservedSeats << "\n";
        cout << "Available Seats: " << totalSeats - reservedSeats << "\n";
    }

    string getTrainNumber() const { return trainNumber; }

    const Route& getRoute() const { return route; }

private:
    string trainNumber;
    Route route;
    string schedule;
    int totalSeats;
    vector<bool> seats;
};

class Ticket {
public:
    Ticket(const string& passengerName, string schedule, int seatNumber, Route& route, const Train& train)
        : passengerName(passengerName), schedule(schedule), seatNumber(seatNumber), route(route), train(train)
    {}
    string getPassengerName() const { return passengerName; }
    string getSchedule() const { return schedule; }
    int getSeatNumber() const { return seatNumber; }
    const Route& getRoute() const { return route; }
    const Train& getTrain() const { return train; }

private:
    string passengerName;
    string schedule;
    int seatNumber;
    Route route;
    Train train;
};

class Passenger {
public:
    Passenger(const string& passenger_name, const string& password)
        : passenger_name(passenger_name), password(password)
    {}
    string getPassengername() const { return passenger_name; }
    string getPassword() const { return password; }
    void addTicket(Ticket& newTicket){ tickets.push_back(newTicket); }

    void removeTicket(int index)
    {
        vector<Ticket>::iterator i = tickets.begin();
        i = i + index - 1;
        tickets.erase(i);
    }

    void printAllTickets() const
    {
        int i = 0;
        for (i = 0; i < tickets.size(); i++) {
            cout << "\n\t\t------ Ticket " << i + 1 << " ------" << endl;
            cout << "\t\t\tPassenger: " << tickets[i].getPassengerName() << endl;
            cout << "\t\t\tRoute: " << tickets[i].getRoute().getName() << " ("
                 << tickets[i].getRoute().getDeparture() << " to "
                 << tickets[i].getRoute().getArrival() << ")\n";
            cout << "\t\t\tTrain Number: " << tickets[i].getTrain().getTrainNumber() << endl;
            cout << "\t\t\tSchedule: " << tickets[i].getTrain().getSchedule() << endl;
            cout << "\t\t\tSeat Number: " << tickets[i].getSeatNumber() << endl;
        }
    }

    int numberOfTickets() const { return tickets.size(); }

    Ticket& getTicket(int index) { return tickets[index - 1]; }

private:
    string passenger_name;
    string password;
    vector<Ticket> tickets;
};

class ReservationSystem {
public:
    ReservationSystem()
    {
        routes.push_back(Route("R001", "Astana", "Almaty", 1320));
        routes.push_back(Route("R002", "Almaty", "Atyrau", 2670));
        routes.push_back(Route("R003", "Atyrau", "Astana", 1990));

        trains.push_back(Train("T001", routes[0], "From Mon 18:46 To Tue 08:57", 15));
        trains.push_back(Train("T002", routes[0], "From Thu 23:59 To Fri 20:32", 20));
        trains.push_back(Train("T003", routes[1], "From Thu 13:07 To Sun 17:42", 16));
        trains.push_back(Train("T004", routes[2], "From Wed 22:26 To Fri 12:36", 18));
    }

    void registerPassenger(const string& passenger_name, const string& password)
    {
        passengers.push_back(Passenger(passenger_name, password));
        cout << "\n\t\tPassenger registered successfully. Please log in to continue!\n";
    }

    bool authenticatePassenger(const string& passenger_name, const string& password)
    {
        for (const Passenger& passenger : passengers) {
            string lowercasePassengername = passenger.getPassengername();
            string lowercaseInputPassengername = passenger_name;
            transform(lowercasePassengername.begin(), lowercasePassengername.end(),
                      lowercasePassengername.begin(), ::tolower);
            transform(lowercaseInputPassengername.begin(), lowercaseInputPassengername.end(),
                      lowercaseInputPassengername.begin(), ::tolower);

            if (lowercasePassengername == lowercaseInputPassengername
                && passenger.getPassword() == password) {
                return true;
            }
        }
        return false;
    }

    Passenger& findPassenger(string passenger_name)
    {
        for (int i = 0; i < passengers.size(); i++) {
            if (passengers[i].getPassengername() == passenger_name) {
                return passengers[i];
            }
        }
        return passengers[passengers.size() - 1];
    }

    void displayRoutes() const
    {
        cout << "\n\t\t------ Available Routes ------\n";
        for (const Route& route : routes) {
            cout << "\n\t\tRoute Name: " << route.getName()
                 << " (" << route.getDeparture() << " to " << route.getArrival() << ")\n";
            cout << "\t\t\tDistance: " << route.getDistance() << " km" << endl;
        }
    }

    void displayTrains() const
    {
        cout << "\t\t------ Available Trains ------\n";
        for (const Train& train : trains) {
            train.displayTrainInfo();
            cout << endl;
        }
    }

    void displayTrainsForRoute(int selectedRoute) const
    {
        cout << "\t\t\tTrains available for Route " << routes[selectedRoute - 1].getName() << ":\n";
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].getRoute().getName() == routes[selectedRoute - 1].getName()) {
                trains[i].displayTrainInfo();
                cout << endl;
            }
        }
    }

    void bookTicket(const string& passenger_name)
    {
        int selectedRoute, selectedTrain, selectedSeat;

        displayRoutes();
        cout << "\n\t\tSelect a Route (Enter the Route Number): ";
        string routeNumber;
        cin >> routeNumber;

        bool validRoute = false;
        for (int i = 0; i < routes.size(); i++) {
            if (routeNumber == routes[i].getName()) {
                selectedRoute = i + 1;
                validRoute = true;
                break;
            }
        }

        if (!validRoute) {
            cout << "\n\tInvalid route number. Please enter a valid route number.\n";
            return; 
        }

        cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        displayTrainsForRoute(selectedRoute);

        cout << "\n\t\tSelect a Train (Enter the Train Number): ";
        string trainNumber;
        cin >> trainNumber;

        validRoute = false;
        for (int i = 0; i < trains.size(); i++) {
            if (trainNumber == trains[i].getTrainNumber() && 
                trains[i].getRoute().getName() == routes[selectedRoute - 1].getName()) {
                selectedTrain = i + 1;
                validRoute = true;
                break;
            }
        }

        if (!validRoute) {
            cout << "\n\tInvalid train number. Please enter a valid train number for the selected route.\n";
            return; 
        }

        cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "\n\t\tEnter the seat number you want to book: ";
        cin >> selectedSeat;

        if (cin.fail() || selectedSeat < 1
            || selectedSeat > trains[selectedTrain - 1].getTotalSeats()) {
            cout << "\n\tInvalid seat number. Please enter a valid seat number for the selected train.\n";
            return; 
        }

        if (trains[selectedTrain - 1].reserveSeat(
                selectedSeat)) {
            Ticket ticket(passenger_name, trains[selectedTrain - 1].getSchedule(), 
                          selectedSeat, routes[selectedRoute - 1], trains[selectedTrain - 1]);
            Passenger& passenger = findPassenger(passenger_name);
            passenger.addTicket(ticket);
            cout << "\n\t\t\tTicket booked successfully!\n";
            cout << "\t\t\tPassenger: " << ticket.getPassengerName() << "\n";
            cout << "\t\t\tTrain Number: " << trains[selectedTrain - 1].getTrainNumber() << "\n";
            cout << "\t\t\tRoute: " << ticket.getRoute().getName() << " ("
                 << ticket.getRoute().getDeparture() << " to " << ticket.getRoute().getArrival() << ")\n";
            cout << "\t\t\tSeat Number: " << ticket.getSeatNumber() << "\n";
            trains[selectedTrain - 1].displayTrainStatus();
        }
        else {
            cout << "\n\tSeat booking failed. The seat is already reserved or does not exist.\n";
        }
    }

    void cancelTicket(const string& passenger_name)
    {
        int ticketDel = -1;
        Passenger& passenger = findPassenger(passenger_name);
        if (passenger.numberOfTickets() <= 0) {
            cout << "\n\t\t\nNo Tickets Booked!\n";
            return;
        }
        passenger.printAllTickets();

        cout << "\t\t\nSelect the ticket to be cancelled... ";
        cin >> ticketDel;

        cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        if (cin.fail()
            || ticketDel > passenger.numberOfTickets()) {
            cout << "\tInvalid Ticket Selected! Please select a valid ticket\n";
            return;
        }
        else {
            cout << "\t\t\tTicket canceled successfully.\n";
            Ticket ticket = passenger.getTicket(ticketDel);
            Train train = ticket.getTrain();
            for (int i = 0; i < trains.size(); i++) {
                if (trains[i].getTrainNumber() == train.getTrainNumber()) {
                    trains[i].cancelSeat(ticket.getSeatNumber());
                }
            }
            passenger.removeTicket(ticketDel);
        }
    }

    void run()
    {
        while (true) {
            cout << "\n\t🚂 🚃 🚃 🚃  Welcome to the Train Ticketing System  🚃 🚃 🚃 🚃\n\n";
            cout << "\t\t\t1. Register"
                    "\n\t\t\t2. Log In"
                    "\n\t\t\t3. Exit\t\t\t\n";
            cout << "\n\t\t\tEnter your option: ";
            int option;
            cin >> option;

            if (option == 1) {
                string passenger_name, password;
                cout << "\n\t\t\tEnter passenger name: ";
                cin >> passenger_name;
                cout << "\t\t\tEnter password: ";
                cin >> password;
                registerPassenger(passenger_name, password);
            }
            else if (option == 2) {
                string passenger_name, password;
                cout << "\n\t\t\tEnter passenger name: ";
                cin >> passenger_name;
                cout << "\t\t\tEnter password: ";
                cin >> password;
                if (authenticatePassenger(passenger_name, password)) {
                    cout << "\n\t\t\tSuccessful Log In!\n";
                    passengerMenu(passenger_name);
                }
                else {
                    cout << "\n\t\tAuthentication failed! Please check your passenger name and password.\n";
                }
            }
            else if (option == 3) {
                cout << "\n\t\tExiting the Train Reservation System. Goodbye!\n";
                break;
            }
        }
    }

    void passengerMenu(string passenger_name)
    {
        int option = 0;
        while (true) {
            cout << "\n\t🚞 🧳 🚋 💺  Welcome to the Passenger Menu  💺 🚋 🧳 🚞\n\n";
            cout << "\t\t\t1. Display Routes"
                    "\n\t\t\t2. Display Trains"
                    "\n\t\t\t3. Book Ticket"
                    "\n\t\t\t4. Cancel Ticket"
                    "\n\t\t\t5. Log Out\n";
            cout << "\n\t\t\tEnter your option: ";
            cin >> option;

            if (option == 1) {displayRoutes();}
            else if (option == 2) {displayTrains();}
            else if (option == 3) {bookTicket(passenger_name);}
            else if (option == 4) {cancelTicket(passenger_name);}
            else if (option == 5) {
                cout << "\n\t\t\tSuccessful Log Out.\n";
                break;}
        }
    }

private:
    vector<Passenger> passengers;
    vector<Route> routes;
    vector<Train> trains;

    void displayTrainsForRoute(int selectedRoute)
    {
        cout << "\t\t\tTrains for Route " << routes[selectedRoute - 1].getName() << ":\n";
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].getRoute().getName() == routes[selectedRoute - 1].getName()) {
                trains[i].displayTrainInfo();
                cout << endl;
            }
        }
    }
};

int main()
{
    ReservationSystem system;
    system.run();
    return 0;
}
