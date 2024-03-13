package com.example.jnifirstapplication;

import java.io.Serializable;
import java.util.List;

public class Result implements Serializable {
   private String firstName;
   private int rollNo;
   private String phoneNo;
   private boolean pass;
   private double percentage;

   public Result(String firstName, int rollNo, String phoneNo, boolean pass, double percentage) {
      this.firstName = firstName;
      this.rollNo = rollNo;
      this.phoneNo = phoneNo;
      this.pass = pass;
      this.percentage = percentage;
   }

   public String getFirstName() {
      return firstName;
   }

   public int getRollNo() {
      return rollNo;
   }

   public String getPhoneNo() {
      return phoneNo;
   }

   public boolean isPass() {
      return pass;
   }

   public double getPercentage() {
      return percentage;
   }
}
