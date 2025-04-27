#include <iostream>
#include <string>
using namespace std;

enum enGameLevel
{
    Easy = 1,
    Medium = 2,
    Hard = 3,
    MixLevels = 4
};
enum enGameOp
{
    Addition = 1,
    Subtraction = 2,
    Multiplication = 3,
    Division = 4,
    MixOp = 5
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

string GetOpType(enGameOp OpType)
{
    switch (OpType)
    {
    case Addition:
        return "+";
    case Subtraction:
        return "-";
    case Multiplication:
        return "x";
    case Division:
        return "/";
    case MixOp:
        // Randomly pick an operation for MixOp
        int randOp = rand() % 4 + 1; // Random number between 1 and 4
        switch (randOp)
        {
        case 1:
            return "+";
        case 2:
            return "-";
        case 3:
            return "x";
        case 4:
            return "/";
        default:
            return "+";
        }
    }
    return "";
}

struct stQuestion
{
    int Number1;
    int Number2;
    int CorrectAnswer;
    int WrongAnswer;
    bool Pass;
    enGameLevel Level;
    enGameOp OpType;
};



void DisplayScore(int CorrectAnswerCount, int WrongAnswerCount) {
    // Clear screen
    cout << "\033[2J\033[1;1H";  // ANSI code to clear screen

    // Score Display
    cout << "\n==========================================" << endl;
    cout << "            \033[1;33mYour Final Score\033[0m" << endl;
    cout << "==========================================" << endl;
    cout << "\033[1;32mCorrect Answers: \033[0m" << CorrectAnswerCount << endl;
    cout << "\033[1;31mWrong Answers:   \033[0m" << WrongAnswerCount << endl;

    // Performance Feedback
    if (CorrectAnswerCount > WrongAnswerCount) {
        cout << "\n\033[1;32mWell done, you've passed with an excellent performance!\033[0m" << endl;
        cout << "You're a math genius! Keep up the great work!" << endl;
    }
    else {
        cout << "\n\033[1;31mOops! You didn't pass this time.\033[0m" << endl;
        cout << "Don't worry! You're almost there. Keep practicing, and you'll get better!" << endl;
    }

    // Fun motivational message
    cout << "\n==========================================" << endl;
    cout << "Remember, practice makes perfect. \033[1;34mYou got this!\033[0m" << endl;
    cout << "==========================================" << endl;
}



void WelcomeMessage()
{
    cout << "==============================================" << endl;
    cout << "||      Welcome to the Ultimate Math Game!   ||" << endl;
    cout << "||      Created by: Ahmad Shdeed (Onyxl)     ||" << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << ">> Follow me on my socials:" << endl;
    cout << ">> GitHub:      github.com/0nyxl" << endl;
    cout << ">> X (Twitter): x.com/0nyxl" << endl;
    cout << ">> Email:       i0nyxl@hotmail.com" << endl;
    cout << endl;
    cout << "==============================================" << endl;
    cout << ">> Ready to challenge your brain with math?" << endl;
    cout << ">> Solve problems, sharpen your skills, and have fun!" << endl;
    cout << "==============================================" << endl;
}

int HowManyQuestions()
{
    int input;
    cout << "\nHow many questions do you think you can solve? ";
    while (!(cin >> input) || input <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Oops! Please enter a valid number greater than 0: ";
    }
    return input;
}

enGameLevel SelectLevel()
{
    short input = 0;
    cout << "\nChoose a difficulty level:\n";
    cout << "[1] Easy\n";
    cout << "[2] Medium\n";
    cout << "[3] Hard\n";
    cout << "[4] Mix\n";
    cout << "Your choice: ";
    while (true)
    {
        cin >> input;
        if (cin.fail() || input < 1 || input > 4)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please choose a number between 1 and 4: ";
        }
        else
        {
            break;
        }
    }
    return static_cast<enGameLevel>(input);
}

enGameOp SelectOperation()
{
    short input = 0;
    cout << "\nSelect the game operation:\n";
    cout << "[1] Addition (+)\n";
    cout << "[2] Subtraction (-)\n";
    cout << "[3] Multiplication (*)\n";
    cout << "[4] Division (/)\n";
    cout << "[5] Mix (Random)\n";
    cout << "Your choice: ";
    while (true)
    {
        cin >> input;
        if (cin.fail() || input < 1 || input > 5)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please choose a number between 1 and 5: ";
        }
        else
        {
            break;
        }
    }
    return static_cast<enGameOp>(input);
}

stQuestion GenerateQuestion(enGameLevel Level, enGameOp OpType)
{
    stQuestion Question;

    if (Level == enGameLevel::MixLevels)
    {
        Level = static_cast<enGameLevel>(RandomNumber(1, 3));
    }
    Question.Level = Level;

    switch (Level)
    {
    case enGameLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enGameLevel::Medium:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enGameLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    if (OpType == enGameOp::MixOp)
    {
        OpType = static_cast<enGameOp>(RandomNumber(1, 4));
    }
    Question.OpType = OpType;

    switch (OpType)
    {
    case Addition:
        Question.CorrectAnswer = Question.Number1 + Question.Number2;
        break;
    case Subtraction:
        Question.CorrectAnswer = Question.Number1 - Question.Number2;
        break;
    case Multiplication:
        Question.CorrectAnswer = Question.Number1 * Question.Number2;
        break;
    case Division:
        while (Question.Number2 == 0)
        {
            Question.Number2 = RandomNumber(1, 100);
        }
        Question.CorrectAnswer = Question.Number1 / Question.Number2;
        break;
    }

    return Question;
}

void Play(int numQuestions, enGameLevel level, enGameOp opType)
{
    int WrongAnswer = 0;
    int CorrectAnswer = 0;
    for (int i = 0; i < numQuestions; i++)
    {
        stQuestion question = GenerateQuestion(level, opType);
        cout << "\nQuestion " << i + 1 << ": " << question.Number1 << " " << GetOpType(question.OpType) << " " << question.Number2 << " = ?" << endl;

        int userAnswer;
        cout << "Your answer: ";
        cin >> userAnswer;

        if (userAnswer == question.CorrectAnswer)
        {
            CorrectAnswer++;
            cout << "Correct!\n";
        }
        else
        {
            WrongAnswer++;
            cout << "Wrong! The correct answer is: " << question.CorrectAnswer << endl;
        }
        
    }
    DisplayScore(CorrectAnswer, WrongAnswer);
}

void PlayGame()
{
    char YesOrNo;
    do
    {
        system("cls");
        WelcomeMessage();
        int numQuestions = HowManyQuestions();
        enGameLevel level = SelectLevel();
        enGameOp opType = SelectOperation();

        Play(numQuestions, level, opType);  // Start playing

        
        cout << "\nWould you like to play again? (Y/N): ";
        cin >> YesOrNo;

    } while (YesOrNo == 'Y' || YesOrNo == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    PlayGame();  // Start the game

    return 0;
}
