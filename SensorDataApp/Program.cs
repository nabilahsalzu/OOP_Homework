class Program
{
    static void Main()
    {
        List<TemperatureRecord> records = new();

        // Main outer loop handles restarting the program for a new location
        while (true)
        {
            // Clear any previous records before starting with a new location
            records.Clear();

            Console.WriteLine("\n=================================");
            Console.Write("Enter location: ");
            string location = Console.ReadLine() ?? "Unknown";

            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine($"\nRecord {i + 1}");

                Console.Write("Enter time (minute): ");
                int time = Convert.ToInt32(Console.ReadLine());

                Console.Write("Enter temperature: ");
                double temperature = Convert.ToDouble(Console.ReadLine());

                // create an object and add it to the list
                TemperatureRecord record = new TemperatureRecord
                {
                    Location = location,
                    Time = time,
                    Temperature = temperature
                };

                records.Add(record);
            }

            bool activeSession = true;
            while (activeSession)
            {
                Console.WriteLine($"\n=== MENU ===");
                Console.WriteLine("a) Compute min and max");
                Console.WriteLine("b) Compute average");
                Console.WriteLine("c) Get temperatures above threshold");
                Console.WriteLine("d) Enter temperature of a new location");
                Console.WriteLine("e) Exit");
                Console.Write("Choose option (a-e): ");

                string option = Console.ReadLine()?.ToLower() ?? "";

                switch (option)
                {
                    // "r => r.Temperature" - lambda expression: Go through each object in the list and take the Temperature value only
                    case "a":
                        double max = records.Max(r => r.Temperature); // For each record (r), take only the Temperature
                        double min = records.Min(r => r.Temperature);

                        Console.WriteLine($"Max: {max}");
                        Console.WriteLine($"Min: {min}");
                        break;

                    case "b":
                        double avg = records.Average(r => r.Temperature); // Take all temperatures (Using lambda expression) and find the average using LINQ
                        Console.WriteLine($"Average: {avg}");
                        break;

                    case "c":
                        Console.Write("Enter threshold: ");
                        double threshold = Convert.ToDouble(Console.ReadLine());

                        var filtered = records.Where(r => r.Temperature > threshold);

                        // Only keep records where temperature is greater than a value
                        foreach (var r in filtered)
                        {
                            Console.WriteLine($"Time: {r.Time} min, Temp: {r.Temperature}");
                        }
                        break;

                    case "d":
                        Console.WriteLine("\nRestarting program for a new location...");
                        
                        // Breaking this inner loop returns control to the outer loop
                        activeSession = false; 
                        break;

                    case "e":
                        Console.WriteLine("Exiting...");
                        return;

                    default:
                        Console.WriteLine("Invalid option.");
                        break;
                }
            }
        }
    }
}

/*
LINQ (Language Integrated Query)
1. Max() - Finds the maximum value in a collection.
2. Min() - Finds the minimum value in a collection.
3. Average() - Calculates the average of a collection of numeric values.
4. Where() - Filters a collection based on a specified condition (predicate).
*/