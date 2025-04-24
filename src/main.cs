// based off of https://github.com/5quirre1/BrainFuck-interpreter/blob/main/src/main.cpp greg

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

public class swag
{
    private List < byte > swagmemory;
    private int pointerggggg;
    public swag(int swagmemorySize = 30000)
    {
        swagmemory = new List < byte > (swagmemorySize);
        for (int i = 0; i < swagmemorySize; ++i)
        {
            swagmemory.Add(0);
        }
        pointerggggg = 0;
    }
    public void executeStuff(string code)
    {
        Stack < int > gregloop = new Stack < int > ();
        for (int i = 0; i < code.Length; ++i)
        {
            char instruction = code[i];
            switch (instruction)
            {
                case '>':
                    ++pointerggggg;
                    if (pointerggggg >= swagmemory.Count)
                    {
                        int oldSize = swagmemory.Count;
                        int newSize = oldSize * 2;
                        if (swagmemory.Capacity < newSize)
                        {
                            swagmemory.Capacity = newSize;
                        }
                        for (int j = oldSize; j < newSize; ++j)
                        {
                            swagmemory.Add(0);
                        }
                    }
                    break;
                case '<':
                    if (pointerggggg > 0)
                    {
                        --pointerggggg;
                    }
                    else
                    {
                        Console.Error.WriteLine("error: pointer out of bounds");
                        return;
                    }
                    break;
                case '+':
                    ++swagmemory[pointerggggg];
                    break;
                case '-':
                    --swagmemory[pointerggggg];
                    break;
                case '.':
                    Console.Write((char) swagmemory[pointerggggg]);
                    break;
                case ',':
                {
                    int inputByte = Console.Read();
                    if (inputByte == -1)
                    {
                        swagmemory[pointerggggg] = 0;
                    }
                    else
                    {
                        swagmemory[pointerggggg] = (byte) inputByte;
                    }
                }
                break;
            case '[':
                if (swagmemory[pointerggggg] == 0)
                {
                    int nestL = 1;
                    while (nestL > 0 && ++i < code.Length)
                    {
                        if (code[i] == '[')
                        {
                            ++nestL;
                        }
                        else if (code[i] == ']')
                        {
                            --nestL;
                        }
                    }
                    if (nestL > 0)
                    {
                        Console.Error.WriteLine("error: unmatched '['");
                        return;
                    }
                }
                else
                {
                    gregloop.Push(i);
                }
                break;
            case ']':
                if (gregloop.Count == 0)
                {
                    Console.Error.WriteLine("error: unmatched ']'");
                    return;
                }
                if (swagmemory[pointerggggg] != 0)
                {
                    i = gregloop.Peek();
                }
                else
                {
                    gregloop.Pop();
                }
                break;
            }
        }
        if (gregloop.Count != 0)
        {
            Console.Error.WriteLine("error: unmatched '['");
        }
    }
    public bool bracketgreg(string code)
    {
        Stack < int > bracketthing = new Stack < int > ();
        for (int i = 0; i < code.Length; ++i)
        {
            if (code[i] == '[')
            {
                bracketthing.Push(i);
            }
            else if (code[i] == ']')
            {
                if (bracketthing.Count == 0)
                {
                    Console.Error.WriteLine($ "error: unmatched ']' at position {i}");
                    return false;
                }
                bracketthing.Pop();
            }
        }
        if (bracketthing.Count != 0)
        {
            Console.Error.WriteLine($ "error: unmatched '[' at position {bracketthing.Peek()}");
            return false;
        }
        return true;
    }
    public void fileexxxxxxxxx(string filename)
    {
        string code = "";
        try
        {
            using(StreamReader file = new StreamReader(filename))
            {
                StringBuilder codeBuilder = new StringBuilder();
                int charCode;
                while ((charCode = file.Read()) != -1)
                {
                    char c = (char) charCode;
                    if (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']')
                    {
                        codeBuilder.Append(c);
                    }
                }
                code = codeBuilder.ToString();
            }
            if (bracketgreg(code))
            {
                executeStuff(code);
            }
        }
        catch (FileNotFoundException)
        {
            Console.Error.WriteLine($ "error: could not open file {filename} (not found)");
            return;
        }
        catch (IOException ex)
        {
            Console.Error.WriteLine($ "error: could not read file {filename} - {ex.Message}");
            return;
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine($ "error: an unexpected error occurred while processing file {filename} - {ex.Message}");
            return;
        }
    }
};
public class Program
{
    public static void Main(string[] args)
    {
        swag interpreter = new swag();
        if (args.Length > 0)
        {
            interpreter.fileexxxxxxxxx(args[0]);
        }
        else
        {
            StringBuilder codeBuilder = new StringBuilder();
            string line;
            Console.WriteLine("enter brainfucm coddde (tupen 'end' to stop):");
            while ((line = Console.ReadLine()) != null && line != "end")
            {
                foreach(char c in line)
                {
                    if (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']')
                    {
                        codeBuilder.Append(c);
                    }
                }
            }
            string code = codeBuilder.ToString();
            Console.WriteLine("\nrunning\n");
            if (interpreter.bracketgreg(code))
            {
                string g = new string('=', 60);
                Console.WriteLine(g);
                interpreter.executeStuff(code);
            }
        }
        Console.WriteLine();
        Console.WriteLine("press enter to exit...");
        Console.ReadLine();
    }
}
