# MVC2
Matrix and vector calculator
This software project is intended as a presentation of my skills in programming.
# Main features
The application has console interface, which allows users to upload matrices or vectors, perform various mathematical operations on them and save results. 
A matrix/vector can only be uploaded if written in the specific format in a .txt file and placed in folders ./saves/matrix or ./saves/vector respectively. These folders are also where results of operations are saved.
# File format
![image](https://user-images.githubusercontent.com/94739492/142732576-728f758e-d14a-4011-b15d-3307a1714801.png)
# C++ features implemented
This project is created by the means of Object-Oriented programming. There are 3 classes: Calc, Matrix, Vector. Matrix and Vector are the child classes of Calc; they are responsible for performing mathematical operations on matrices and vectors respectively and inherit from the parent class methods of loading up from and writing down to files.
The function of the parent class, Calc, is to display interface, create instances of the child classes, call their respective mathematical methods and to run the application in general.
