/*
 * run the code - 
 * > make run
 * 
 * note:
 * DB FEILDS USED - 
 * id, name, marks, percentage, grade
 * 1) Make sure you create your own database with any name and mentioned feilds(make sure you spell them correct and same) and 
 * update your config before running. 
 *
 * 2)to clean unnecessary files after building the file and running once. you can use the command to clean the files -
 * > make clean
 * 
 * A CRUD c++ student management system with SQL Connectivity
 *
 * @author
 * SUBHAM BANERJEE
*/
#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>
#include <iostream>

// edit your config here - like - hostid, userid, password and database name.
char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "";
char DBNAME[] = "student";

std::string calculate_grade(double perc){
    if(perc >= 85){
        return "A+";
    }else if(perc >= 75){
        return "A";
    }else if(perc >= 65){
        return "B+";
    }else if(perc >= 55){
        return "B";
    }else if(perc >= 50){
        return "C";
    }else if(perc >= 45){
        return "D";
    }else{
        return "F";
    }
}

int main(){
    MYSQL* obj;
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string s = "Subham";
    if(!(obj = mysql_init(0))){
        std::cout << "ERROR: MYSQL object could not be created.";
    } else{
        if(!mysql_real_connect(obj, HOST, USER, PASS, DBNAME, 3306, NULL, 0)){
            std::cout << "Database auth failed" << std::endl;
            std::cout << mysql_error(obj) << std::endl;
        } else{
            std::cout << "Logged in." << std::endl;
            while(true){
                int choice;
                std::cout << "\n\n\t\t\t*** STUDENT MANAGEMENT SYSTEM ***   " << std::endl;
                std::cout << "\t1. INSERT RECORD   " << std::endl;
                std::cout << "\t2. SEARCH RECORD   " << std::endl;
                std::cout << "\t3. UPDATE RECORD   " << std::endl;
                std::cout << "\t4. DELETE RECORD   " << std::endl;
                std::cout << "\t5. SHOW RECORDS   " << std::endl;
                std::cout << "\t0. EXIT PROGRAM   " << std::endl;
                std::cout << "\n\n ENTER YOUR CHOICE ->   ";
                std::cin >> choice;
                int id;
                std::string name, grade;
                double marks, perc;
                std::string query;
                switch(choice){
                    case 0:
                        std::cout << "THANKS FOR USING THE PROGRAM!! @COPYRIGHT 2024 SUBHAM BANERJEE" << std::endl;
                        exit(0);
                    case 1:
                        std::cout << "\n\n\t\t\t*** INSERT STUDENT RECORD ***   " << std::endl;
                        std::cout << "\n\nEnter Student Id :   ";
                        std::cin >> id;
                        std::cout << "\n\nEnter Student Name :   ";
                        std::cin.ignore();
                        std::getline(std::cin, name);
                        std::cout << "\n\nEnter Marks :   ";
                        std::cin >> marks;
                        perc = marks / 100 * 100;
                        grade = calculate_grade(perc);
                        query = "INSERT INTO STUDENT(id, name, marks, percentage, grade) VALUES(" +
                        std::to_string(id) + ", '" + name + "', " + std::to_string(marks) + ", " +
                        std::to_string(perc) + ", '" + grade + "')";
                        if (mysql_query(obj, query.c_str())) {
                            std::cerr << "Error executing MySQL query: " << mysql_error(obj) << std::endl;
                        }
                        std::cout << "Student record inserted successfully!" << std::endl;
                        break;
                    case 2:
                        std::cout << "\n\n\t\t\t*** SEARCH STUDENT RECORD ***   " << std::endl;
                        std::cout << "Enter the Student Id: ";
                        std::cin >> id;
                        query = "SELECT * FROM STUDENT WHERE id = " + std::to_string(id);
                        if (mysql_query(obj, query.c_str())) {
                            std::cerr << "Error executing MySQL query: " << mysql_error(obj) << std::endl;
                            return 1;
                        }
                        res = mysql_store_result(obj);
                        if (!res) {
                            std::cerr << "Error retrieving result set: " << mysql_error(obj) << std::endl;
                            return 1;
                        }
                        if (mysql_num_rows(res) == 0) {
                            std::cout << "No student record found with ID: " << id << std::endl;
                         } else {
                        row = mysql_fetch_row(res);
                        std::cout << "\n_________________\n";
                            std::cout << "Student_Id: " << row[0] 
                            << ", \nName: " << row[1] 
                            << ", \nMarks: " << row[2] 
                            << ", \nPercentage: " << row[3] 
                            << ", \nGrade: " << row[4];
                            std::cout << "\n_________________\n";
                        }
                        mysql_free_result(res);
                        break;
                    case 3:
                        std::cout << "\n\n\t\t\t*** UPDATE STUDENT RECORD ***   " << std::endl;
                        std::cout << "Enter Student Id to update: ";
                        std::cin >> id;
                        std::cout << "\n\nEnter new Student Name: ";
                        std::cin.ignore();
                        std::getline(std::cin, name);
                        std::cout << "Enter new Marks: ";
                        std::cin >> marks;
                        perc = marks / 100 * 100;
                        grade = calculate_grade(marks);
                        query = "UPDATE STUDENT SET name = '" + name + "', marks = " + std::to_string(marks) +
                                ", percentage = " + std::to_string(perc) + ", grade = '" + grade + "' WHERE id = " + std::to_string(id);

                        if (mysql_query(obj, query.c_str())) {
                            std::cerr << "Error executing MySQL query: " << mysql_error(obj) << std::endl;
                        } else {
                            std::cout << "Student record with ID " << id << " updated successfully!" << std::endl;
                        }
                        break;
                    case 4:
                        std::cout << "\n\n\t\t\t*** DELETE STUDENT RECORD ***   " << std::endl;
                        std::cout << "Enter the Student Id: ";
                        std::cin >> id;
                        query = "DELETE FROM STUDENT WHERE id = " + std::to_string(id);
                        if (mysql_query(obj, query.c_str())) {
                            std::cerr << "Error executing MySQL query: " << mysql_error(obj) << std::endl;
                            return 1;
                        }
                        std::cout << "Student with id :" << id << " deleted from database!" << std::endl;
                        break;
                    case 5:
                        if (mysql_query(obj, "SELECT * FROM STUDENT")) {
                            std::cerr << "Error executing MySQL query: " << mysql_error(obj) << std::endl;
                        }
                        res = mysql_store_result(obj);
                        if (!res) {
                            std::cerr << "Error retrieving result set: " << mysql_error(obj) << std::endl;
                            return 1;
                        }
                        while ((row = mysql_fetch_row(res))) {
                            std::cout << "\n_________________\n";
                            std::cout << "Student_Id: " << row[0] 
                            << ", \nName: " << row[1] 
                            << ", \nMarks: " << row[2] 
                            << ", \nPercentage: " << row[3] 
                            << ", \nGrade: " << row[4];
                            std::cout << "\n_________________\n";
                        }
                        mysql_free_result(res);
                        break;
                    default:
                        std::cout << "INVALID COMMAND!!... DID YOU WANT TO EXIT(TYPE 0 FOR EXIT)..." << std::endl;
                }
            }
        }
    }
    mysql_close(obj);
}