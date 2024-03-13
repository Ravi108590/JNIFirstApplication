package com.example.jnifirstapplication;

import java.io.Serializable;

public class Marks implements Serializable {

    String subjectName;
    int subjectMark;

    public Marks(String subjectName, int subjectMark) {
        this.subjectName = subjectName;
        this.subjectMark = subjectMark;
    }

    public String getSubjectName() {
        return subjectName;
    }

    public void setSubjectName(String subjectName) {
        this.subjectName = subjectName;
    }

    public int getSubjectMark() {
        return subjectMark;
    }

    public void setSubjectMark(int subjectMark) {
        this.subjectMark = subjectMark;
    }
}
