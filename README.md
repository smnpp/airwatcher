# airwatcher
application project to monitor and analyze air quality by ATMO index

This repository contains the source code for the AirWatcher project. AirWatcher is a system designed to [briefly describe the purpose of the project]. For detailed information, refer to the project specification document (provided as `project.pdf`).

## Compilation Instructions

### Main Application

To run the main application:

1. Navigate to the root of the `src` folder.
2. Execute the following command to build the application:
make
3. Run the executable:
./AirWatcher
4. Follow the on-screen instructions to use the application.

Credentials for initial login:
- **Role:** Agency
- **Username:** admin
- **Password:** admin

To clean the build files after use, run:
make clean

### Validation and Unit Tests

To run validation and unit tests:

1. Navigate to the root of the `src` folder.
2. Execute the following command to build the test executable:

make -f mktest
3. Run the test executable:
./validation_exec
4. Follow the on-screen instructions to perform validation and unit tests. Note that test scenarios will be displayed in the terminal.

To clean the build files after running tests, execute:
make -f mktest clean