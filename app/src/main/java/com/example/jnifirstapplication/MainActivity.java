package com.example.jnifirstapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Parcelable;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.example.jnifirstapplication.databinding.ActivityMainBinding;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'jnifirstapplication' library on application startup.
    static {
        System.loadLibrary("jnifirstapplication");
    }

    private ActivityMainBinding binding;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText; // binding the textView into the tv
        tv.setText(stringFromJNI());// into the tv setting the data

        binding.textView2.setText(process());
        binding.addBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
               try {
                   int num1 = Integer.parseInt(binding.numOne.getText().toString());
                   int num2 = Integer.parseInt(binding.numTwo.getText().toString());
                   if (num1 != 0 || num2 != 0)
                   {
                       binding.textView.setText(Integer.toString(additionNum(num1,num2)));
                   }
                   else{
                       Toast.makeText(MainActivity.this, "Please fill all the Details", Toast.LENGTH_SHORT).show();
                   }
               }catch (NumberFormatException e)
               {
                   Toast.makeText(MainActivity.this, "Please Enter All the Data", Toast.LENGTH_SHORT).show();
               }
            }
        });

        binding.subBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {
                    int num1 = Integer.parseInt(binding.numOne.getText().toString());
                    int num2 = Integer.parseInt(binding.numTwo.getText().toString());
                    if (num1 != 0 || num2 != 0)
                    {
                        binding.textView.setText(Integer.toString(subtraction(num1,num2)));
                    }
                    else{
                        Toast.makeText(MainActivity.this, "Please fill all the Details", Toast.LENGTH_SHORT).show();
                    }
                }catch (NumberFormatException e)
                {
                    Toast.makeText(MainActivity.this, "Please Enter All the Data", Toast.LENGTH_SHORT).show();
                }
            }
        });

        binding.sumOfarray.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int sum = arraySum(new int[] {1,2,3,4,5});
                binding.textView.setText(String.valueOf(sum));
                Log.d("JNIExample", "Sum from JNI: " + sum);
            }
            });

        binding.stringconcat.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String addString = concatenateString("Ravi", "Pathak");
                binding.textView.setText(addString);
            }
        });

        binding.randomNum.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                binding.textView.setText(""+getRandomNumber());
            }
        });

        binding.createStudent.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Student information = createStudent();
                Log.d("data", "Your Data:" + information.getMarks());

                List<Marks> list =information.getMarks();
                List<Marks> res = new ArrayList<>();
                String result = "";

                for (Marks marks : list){
                    String sub = marks.subjectName;
                    int mark = marks.subjectMark;
                    Log.d("TAG",sub+mark);
                    result+=sub+" "+mark+", ";
                    res.add(new Marks(sub,mark));
                }

                binding.textView.setText("FirstName:" + information.getFname() + "," + "LastName:" + information.getLname() + ","
                        + "PhoneNo:" + information.getPhoneNo() + "," + "Address:" + information.getAddress()
                        + "," + information.getRollNo() + "," + "Marks:" + result);
            }
        });


        List<Marks> marks = new ArrayList<>();
        marks.add(new Marks("Math", 98));
        marks.add(new Marks("Science", 97));

// Create a Student object with the list of Marks
        Student student = new Student("Ravikumar", "Pathak", "1234567890", "Ahmedabad", 12345, marks);
        binding.getStudentDetails.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Student fetchingData = getStudentDetails(student);
                List<Marks> list = fetchingData.getMarks();
                String result = "";

                for (Marks marks : list) {
                    String sub = marks.getSubjectName();
                    int mark = marks.getSubjectMark();
                    Log.d("sub", "Subject:" + sub);
                    Log.d("mark", "Mark:" + mark);
                    result += sub + " " + mark + ", ";
                }

                Log.d("getData", "GetData:" + fetchingData.getFname());
                binding.textView.setText("FirstName:" + fetchingData.getFname() + "," +
                        "LastName:" + fetchingData.getLname() + "," +
                        "PhoneNo:" + fetchingData.getPhoneNo() + "," +
                        "Address:" + fetchingData.getAddress() + "," +
                        "RollNo:" + fetchingData.getRollNo() + "," +
                        "Marks:" + result);
            }
    });

        binding.result.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                List<Marks> marksList = new ArrayList<>();
                // Add your Marks objects to the marksList here
                marksList.add(new Marks("Math", 20));
                marksList.add(new Marks("Science", 9));

                // Call the JNI function to calculate the result
                Result result = calculateResult("Ravikumar", 12345, "1234567890", marksList);
                // Update UI with the resul
                Log.d("result", "Data:"+result.getFirstName());
                binding.textView.setText(""+result.getFirstName()+" "+result.getPhoneNo()+" "+result.getRollNo() + " "+result.getPercentage()+ " "+result.isPass());
            }
        });

        binding.sendStudentEnum.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EnumStudent student = EnumStudent.PARTHIV;
                int enumValue = getEnumStudentValue(student);
                Log.d("EnumValue", "Enum Value: " + enumValue);
                binding.textView.setText(""+enumValue);
            }
        });

        binding.sendStudent.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ArrayList<Student> studentsList = new ArrayList<>();
                studentsList.add(new Student("RaviKumar Pathak"));
                studentsList.add(new Student("ShyamKumar Mishra"));

                String result = sendStudents(studentsList);
                Log.d("JNIResult", "Result from JNI: " + result);
                binding.textView.setText(""+result);
            }
        });

        binding.basicType.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int anInt = 42;
                long aLong = 123456789L;
                boolean aBoolean = true;
                float aFloat = 3.14f;
                double aDouble = 2.71828;
                String aString = "Hello from MainActivity";

                // Call the native method
                boolean result = basicTypes(anInt, aLong, aBoolean, aFloat, aDouble, aString);
                binding.textView.setText(""+result);

                // Use the result as needed
                if (result) {
                    Toast.makeText(MainActivity.this, "Validation successful", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(MainActivity.this, "Validation failed", Toast.LENGTH_SHORT).show();
                }
            }
        });

        binding.getBundle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Create some dummy data
                List<Marks> marksList = new ArrayList<>();
                marksList.add(new Marks("Subject1", 90));
                marksList.add(new Marks("Subject2", 85));
                marksList.add(new Marks("Subject3", 88));

// Create a Student object
                Student student = new Student("John", "Doe", "1234567890", "123 Main St", 101, marksList);

// Display Student data in UI
                String result = "";

                for (Marks mark : marksList) {
                    String sub = mark.getSubjectName();
                    int num = mark.getSubjectMark();
                    Log.d("subject", "Subject:" + sub);
                    Log.d("mark", "mark:" + num);
                    result += sub + " " + num + " "; // Fix here, concatenate subject name and mark
                }

                binding.textView.setText("Name: " + student.getFname() + " " + student.getLname() + "," +
                        "Phone: " + student.getPhoneNo() + "," +
                        "Address: " + student.getAddress() + "," +
                        "Roll No: " + student.getRollNo() + "," +
                        "Marks: " + result);

            }
        });
    }

    // creating the Native method for the cpp
    public native String process(); // make sure this method should be same as in cpp

    // creating own method
    public String processInJava() {
        return "processed in java";
    }

    public native int additionNum(int num1, int num2);
    public native int subtraction(int num1, int num2);
    public native int arraySum(int[] arr);

    public native String concatenateString(String str1, String st2);

    public native int getRandomNumber();
    public native Student createStudent();

    public native Student getStudentDetails(Student student);
    public native Result calculateResult(String firstName, int rollNo, String phoneNo, List<Marks> marksList);
    public native int getEnumStudentValue(EnumStudent enumStudent);
    public native String sendStudents(ArrayList<Student> arrayListOfStudents);
    public native boolean basicTypes(int anInt, long aLong, boolean aBoolean, float aFloat,
                                     double aDouble, String aString);



    /**
     * A native method that is implemented by the 'jnifirstapplication' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}