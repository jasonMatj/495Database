//
//  main.cpp
//  database
//
//  Created by matianju on 11/6/17.
//  Copyright © 2017 TianjuMa. All rights reserved.
//

#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;

void login();
void transcript();
void course_detail();

string student_id;
string student_password;

MYSQL *conn = mysql_init(NULL);
MYSQL *connection_result;

int main (int argc, const char * argv[]) {
    mysql_real_connect(conn, "localhost", "root", "Ma930729", "project3-nudb", 0, 0, 0);
    if (connection_result == NULL) {
        //unable to connect
        printf("Oh Noes!\n"); }
    else
    {
        printf("You are now connected. Welcome!\n");
    }
    
    while (true) {
        login();
        string ope_num;
        cout << "please enter the operation number you want to take now:\n";
        cout << "1 : student menu.\n";
        cout << "2 : student transcript.\n";
        cin >> ope_num;
        if (ope_num == "2") {
            transcript();
        }
    }
}

void login() {
    cout << "please enter your student id:\n";
    cin >> student_id;
    
    cout << "please enter your pasword:\n";
    cin >> student_password;
 
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    
    string statement ="SELECT * FROM student WHERE Id = '"+student_id+"' and Password = '"+student_password+"';";
    
    mysql_query(conn, statement.c_str());
    
    res_set = mysql_store_result(conn);
    int numrows = (int)mysql_num_rows(res_set);
    // Display results
    if (numrows == 0) {
        cout << "No match!!!!!!!!\n";
    }
    for (int i = 0; i < numrows; i++) {
        row = mysql_fetch_row( res_set );
        if( row != NULL ) {
            cout << "ID : " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
        }
    }
    // free resources
    mysql_free_result( res_set );
}

void transcript() {
    MYSQL_RES *res_set;
    MYSQL_ROW row;
    
    string statement ="SELECT UoSCode, Grade FROM transcript WHERE StudId = '"+student_id+"';";
    
    mysql_query(conn, statement.c_str());
    
    res_set = mysql_store_result(conn);
    int numrows = (int)mysql_num_rows(res_set);
    
    if (numrows == 0) {
        cout << "This student hasn't taken any course yet!!!!!!!!!!!!!!!!!!!\n";
    }
    for (int i = 0; i < numrows; i++) {
        row = mysql_fetch_row( res_set );
        if( row != NULL ) {
            cout << "UoSCode : " << row[0] << endl;
            if (row[1] == NULL) {
                cout << "Grade: " << "NULL" << endl;
            } else {
                cout << "Grade: " << row[1] << endl;
            }
            cout << "\n";
        }
    }
    // free resources
    mysql_free_result( res_set );
    
    string ope_num;
    cout << "Please enter the next operation you want to take:\n";
    cout << "1: Go to Course Details.\n";
    cout << "2: Go to Stduent Menu.\n";
    cin >> ope_num;
    
    if (ope_num == "1") {
        course_detail();
    }
}

void course_detail() {
    MYSQL_RES *res_set1;
    MYSQL_ROW row1;
    
    string course_num;
    cout << "Please enter the course number you want to inspect:\n";
    cin >> course_num;
    
    
    string statement = "select a.UoSCode, a.UoSName, a.Year, a.Semester, a.Enrollment, a.MaxEnrollment, a.Name, b.Grade from( select UoSCode, UoSName, Year, Semester, Enrollment, MaxEnrollment, Name from (unitofstudy inner join uosoffering using(UoSCode)) inner join faculty on Id = InstructorId where UoSCode = ( select UoSCode from transcript where StudId = '"+student_id+"' and UoSCode = '"+course_num+"') and Semester = (select Semester from transcript where StudId = '"+student_id+"' and UoSCode = '"+course_num+"') and Year = (select Year from transcript where StudId = "+student_id+" and UoSCode = '"+course_num+"')) a, transcript as b where b.UoSCode = '"+course_num+"' and b.StudId = '"+student_id+"';";

    mysql_query(conn, statement.c_str());
    
    res_set1 = mysql_store_result(conn);
    int numrows = (int)mysql_num_rows(res_set1);
    
    if (numrows == 0) {
        cout << "Invalid Course Number !!!!!!!!!!!!!!!!!!!\n";
    }
    for (int i = 0; i < numrows; i++) {
        row1 = mysql_fetch_row( res_set1 );
        if( row1 != NULL ) {
            cout << "UoSCode : " << row1[0] << endl;
            cout << "UoSName: " << row1[1] << endl;
            cout << "Year : " << row1[2] << endl;
            cout << "Semester : " << row1[3] << endl;
            cout << "Enrollment : " << row1[4] << endl;
            cout << "MaxEnrollment : " << row1[5] << endl;
            cout << "Name : " << row1[6] << endl;
            if (row1[7] == NULL) {
                cout << "Grade: " << "NULL" << endl;
            } else {
                cout << "Grade: " << row1[7] << endl;
            }
            cout << "\n";
        }
    }
    // free resources
    mysql_free_result( res_set1 );
}