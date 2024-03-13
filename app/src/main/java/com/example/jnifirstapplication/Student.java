package com.example.jnifirstapplication;

import android.os.Bundle;

import java.io.Serializable;
import java.util.List;

public class Student implements Serializable {
    private String fname;
    private String lname;
    private String phoneNo;
    private String address;
    private int rollNo;
    private List<Marks> marks;

    public Student(String fname, String lname, String phoneNo, String address, int rollNo, List<Marks> marks) {
        this.fname = fname;
        this.lname = lname;
        this.phoneNo = phoneNo;
        this.address = address;
        this.rollNo = rollNo;
        this.marks = marks;
    }

    public Student(int rollNo, String fname, String phoneNo, List<Marks> marks) {
        this.rollNo = rollNo;
        this.fname = fname;
        this.phoneNo= phoneNo;
        this.marks = marks;
    }

    public Student(String fname) {
        this.fname = fname;
    }


    public String getFname() {
        return fname;
    }

    public void setFname(String fname) {
        this.fname = fname;
    }

    public String getLname() {
        return lname;
    }

    public void setLname(String lname) {
        this.lname = lname;
    }

    public String getPhoneNo() {
        return phoneNo;
    }

    public void setPhoneNo(String phoneNo) {
        this.phoneNo = phoneNo;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public int getRollNo() {
        return rollNo;
    }

    public void setRollNo(int rollNo) {
        this.rollNo = rollNo;
    }

    public List<Marks> getMarks() {
        return marks;
    }

    public void setMarks(List<Marks> marks) {
        this.marks = marks;
    }

    public native static Student createStudentFromBundle(Bundle bundle);
}
