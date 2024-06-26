# AirWatcher

## About
AirWatcher is an application project designed to monitor and analyze air quality using the ATMO index. The project aims to provide users with real-time data and insights on air quality levels in various regions.

## Compilation Instructions

### Main Application

To run the main application:

1. Navigate to the root of the `src` folder.
2. Execute the following command to build the application:
    ```sh
    make
    ```
3. Run the executable:
    ```sh
    ./AirWatcher
    ```
4. Follow the on-screen instructions to use the application.

Credentials for initial login:
- **Role:** Agency
- **Username:** admin
- **Password:** admin

5. To clean the build files after use, run:
    ```sh
    make clean
    ```

### Validation and Unit Tests

To run validation and unit tests:

1. Navigate to the root of the `src` folder.
2. Execute the following command to build the test executable:
    ```sh
    make -f mktest
    ```
3. Run the test executable:
    ```sh
    ./validation_exec
    ```
4. Follow the on-screen instructions to perform validation and unit tests. Note that test scenarios will be displayed in the terminal.

5. To clean the build files after running tests, execute:
    ```sh
    make -f mktest clean
    ```

## Project Documentation
For detailed information, refer to the project specification document provided as `project.pdf`.

## Authors
- [Melisse Cochet](https://github.com/melissecochet)
- [Saad ElGhissasi](https://github.com/saadelg12)
- [Jassir Habba](https://github.com/Jassir69)
- [Simon Perret](https://github.com/smnpp)

