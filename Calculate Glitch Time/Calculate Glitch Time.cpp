#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <math.h>

// outdated constant probably 1.6 qa area
#define MAXIMUM_POSSIBLE_WEEKLYGAIN 96261846305944.390625
#define HAS_PREMIUM 2;
#define NO_PREMIUM 1;

double PUNCH_TIME = 1.112074927953891;
double REP_TIME = 0.2;
double MUSCLE_KING_TIME = 6.1;
uint8_t PREMIUM = HAS_PREMIUM;
uint8_t BOOSTER = 1.5;
uint8_t PETS = 8;
uint64_t AURA_ADDSTATS = 70;
uint64_t PET_ADDSTATS = 95;

std::string ShortNumberToRepresentiveNumber(std::string number, uint64_t Number)
{
    std::string ShortenedNumber = "";

    for (uint64_t i = 0; i < number.length(); i++)
    {
        if (number[i] == ',')
        {
            ShortenedNumber = ShortenedNumber + '.';
            ShortenedNumber = ShortenedNumber + number[i + 1] + number[i + 2] + number[i + 3];
            break;
        }

        ShortenedNumber = ShortenedNumber + number[i];
    }

    if (Number > 999999999999999999)
    {
        ShortenedNumber = ShortenedNumber + "Qi";
        return ShortenedNumber;
    }

    if (Number > 999999999999999)
    {
        ShortenedNumber = ShortenedNumber + "Qa";
        return ShortenedNumber;
    }

    if (Number > 999999999999)
    {
        ShortenedNumber = ShortenedNumber + 'T';
        return ShortenedNumber;
    }

    if (Number > 999999999)
    {
        ShortenedNumber = ShortenedNumber + 'B';
        return ShortenedNumber;
    }

    if (Number > 999999)
    {
        ShortenedNumber = ShortenedNumber + 'M';
        return ShortenedNumber;
    }

    if (Number > 999)
    {
        ShortenedNumber = ShortenedNumber + 'K';
        return ShortenedNumber;
    }

    return ShortenedNumber;
}


std::string ShortenNumber(uint64_t number)
{
    if (number < 1000)
    {
        std::string returnvalue = std::to_string(number).c_str();
        return returnvalue;
    }

    std::string Number = std::to_string(number);
    std::string NewNumber = "";
    std::string Reversed = "";

    uint8_t Digits = 0;
    for (int64_t i = Number.length() - 1; i >= 0; i--)
    {
        if (Digits == 3 && i >= 0)
        {
            NewNumber = NewNumber + ',';
            Digits = 0;
        }

        NewNumber = NewNumber + Number[i];
        ++Digits;
    }

    for (int64_t i = NewNumber.length() - 1; i >= 0; i--)
    {
        Reversed = Reversed + NewNumber[i];
    }

    return ShortNumberToRepresentiveNumber(Reversed,number);
}

uint64_t difference(uint64_t v1, uint64_t v2)
{
    if (v1 > v2) return (v1 - v2);
    else return (v2 - v1);
}

uint64_t difference(uint64_t v1, uint64_t v2, uint64_t v3)
{
    if (v1 > v2) return (v1 - v2);
    else return (v2 - v1);
}

uint64_t smallest(uint64_t v1, uint64_t v2, uint64_t v3)
{
    if (v1 <= v2 && v1 <= v3) return v1;
    if (v2 <= v1 && v2 <= v3) return v2;
    if (v3 <= v2 && v3 <= v1) return v3;
    return 0;
}

uint64_t biggest(uint64_t v1, uint64_t v2, uint64_t v3)
{
    if (v1 >= v2 && v1 >= v3) return v1;
    if (v2 >= v1 && v2 >= v3) return v2;
    if (v3 >= v2 && v3 >= v1) return v3;
    return 0;
}

void Calculate2Sets(uint64_t WeekHours1, uint64_t WeekHours2)
{
    uint64_t Hours = (WeekHours1 <= WeekHours2 ? WeekHours1 : WeekHours2);
    uint64_t TotalHours = Hours;
    uint64_t Offset = difference(WeekHours1, WeekHours2);

    uint64_t BestFirstSet = 0;
    uint64_t BestSecondSet = 0;
    uint64_t BestFirstSetStrength = 0;
    uint64_t BestSecondSetStrength = 0;
    uint64_t BestFirstSetStrengthGain = 0;
    uint64_t BestSecondSetStrengthGain = 0;
    uint64_t FirstSetStartingHour = 0;
    uint64_t SecondSetStartingHour = 0;
    uint64_t HighestStrengthGain = 0;

    for (Hours; Hours > 1; Hours--)
    {
        for (uint64_t FirstSetHours = 1; FirstSetHours < Hours; FirstSetHours++)
        {
            for (uint64_t SecondSetHours = Hours; SecondSetHours < TotalHours; SecondSetHours++)
            {
                uint64_t SecondSetPetStats = (((SecondSetHours + Offset) * 60 * 60) / PUNCH_TIME) * PET_ADDSTATS;
                uint64_t SecondSetAuraStats = (((SecondSetHours + Offset) * 60 * 60) / PUNCH_TIME) * AURA_ADDSTATS;
                uint64_t SecondSetStrength = ((SecondSetPetStats * PETS) + SecondSetAuraStats) * PREMIUM;
                uint64_t SecondSetStrengthGain = ((((TotalHours - SecondSetHours) * 60 * 60) / REP_TIME) * SecondSetStrength) + ((((TotalHours - SecondSetHours) * 60 * 60) / MUSCLE_KING_TIME) * SecondSetStrength);

                uint64_t FirstSetPetStats = ((FirstSetHours * 60 * 60) / PUNCH_TIME) * PET_ADDSTATS;
                uint64_t FirstSetAuraStats = ((FirstSetHours * 60 * 60) / PUNCH_TIME) * AURA_ADDSTATS;
                uint64_t FirstSetStrength = ((FirstSetPetStats * PETS) + FirstSetAuraStats) * PREMIUM;
                uint64_t FirstSetStrengthGain = ((((Hours - FirstSetHours) * 60 * 60) / REP_TIME) * FirstSetStrength) + ((((Hours - FirstSetHours) * 60 * 60) / MUSCLE_KING_TIME) * FirstSetStrength);

                uint64_t TotalStrengthGained = FirstSetStrengthGain + SecondSetStrengthGain;
                if (TotalStrengthGained > HighestStrengthGain)
                {
                    HighestStrengthGain = TotalStrengthGained;
                    FirstSetStartingHour = FirstSetHours;
                    SecondSetStartingHour = (SecondSetHours + Offset);
                    BestFirstSetStrength = FirstSetStrength;
                    BestSecondSetStrength = SecondSetStrength;
                    BestFirstSetStrengthGain = FirstSetStrengthGain;
                    BestSecondSetStrengthGain = SecondSetStrengthGain;
                    BestFirstSet = FirstSetPetStats;
                    BestSecondSet = SecondSetPetStats;
                    //std::cout << "Gain: " << ShortenNumber(HighestStrengthGain) << "\n" << "Start grinding 1st set at hour " << FirstSetStartingHour << " (Set: " << ShortenNumber(BestFirstSet) << ", Strength: " << ShortenNumber(BestFirstSetStrength) << " a lift, Gain: " << ShortenNumber(BestFirstSetStrengthGain) << ") and grind until second set it ready\n" << "Start grinding second set at hour " << SecondSetStartingHour << " (Set: " << ShortenNumber(BestSecondSet) << ", Strength: " << ShortenNumber(BestSecondSetStrength) << " a lift, Gain: " << ShortenNumber(BestSecondSetStrengthGain) << ") and grind until maintainance" << std::endl;
                }
            }
        }
    }

    std::cout << "Gain: " << ShortenNumber(HighestStrengthGain) << "\n" << "Start grinding 1st set at hour " << FirstSetStartingHour << " (Pet Strength: " << ShortenNumber(BestFirstSet) << ", Strength: " << ShortenNumber(BestFirstSetStrength) << " a lift, Gain: " << ShortenNumber(BestFirstSetStrengthGain) << ") and grind until second set it ready\n" << "Start grinding second set at hour " << SecondSetStartingHour << " (Pet Strength: " << ShortenNumber(BestSecondSet) << ", Strength: " << ShortenNumber(BestSecondSetStrength) << " a lift, Gain: " << ShortenNumber(BestSecondSetStrengthGain) << ") and grind until maintainance" << std::endl;
}

uint64_t valuetolimit(uint64_t Value, uint64_t Limit)
{
    if (Value < Limit) return Value;
    return Limit;
}

#define ADVANCED24_SETS 2
double CalculateSets(double WeekHours, double Divisor, bool Print = true)
{
    double TotalGain = 0;
    double SetPunchingHours = WeekHours / Divisor;
    uint64_t Set = 1;
    while (SetPunchingHours <= WeekHours)
    {
        if (Set <= ADVANCED24_SETS)
        {
            double LiftHours = ((SetPunchingHours * 2 > WeekHours) ? (WeekHours - SetPunchingHours) : SetPunchingHours);
            double Pet = (((SetPunchingHours + 24) * 60 * 60) / PUNCH_TIME) * PET_ADDSTATS;
            double Aura = (((SetPunchingHours + 24) * 60 * 60) / PUNCH_TIME) * AURA_ADDSTATS;
            double Strength = (((Pet * PETS) + Aura) * PREMIUM) * BOOSTER;
            double StrengthGain = (((LiftHours * 60 * 60) / REP_TIME) * Strength) + ((LiftHours * 60 * 60) / MUSCLE_KING_TIME) * Strength;
            TotalGain = TotalGain + StrengthGain;
            if (Print) std::cout << "Gain: " << ShortenNumber(StrengthGain) << "\n" << "Start grinding set [" << Set << "] at " << SetPunchingHours << "h (Strength: " << ShortenNumber(Strength) << " a lift, Gain: " << ShortenNumber(StrengthGain) << ") and grind until next set it ready" << std::endl;
            SetPunchingHours = SetPunchingHours * 2;
            ++Set;
            continue;
        }

        double LiftHours = ((SetPunchingHours * 2 > WeekHours) ? (WeekHours - SetPunchingHours) : SetPunchingHours);
        double Pet = ((SetPunchingHours * 60 * 60) / PUNCH_TIME) * PET_ADDSTATS;
        double Aura = ((SetPunchingHours * 60 * 60) / PUNCH_TIME) * AURA_ADDSTATS;
        double Strength = (((Pet * PETS) + Aura) * PREMIUM) * BOOSTER;
        double StrengthGain = (((LiftHours * 60 * 60) / REP_TIME) * Strength) + ((LiftHours * 60 * 60) / MUSCLE_KING_TIME) * Strength;
        TotalGain = TotalGain + StrengthGain;
        if (Print) std::cout << "Gain: " << ShortenNumber(StrengthGain) << "\n" << "Start grinding set [" << Set << "] at " << SetPunchingHours << "h (Strength: " << ShortenNumber(Strength) << " a lift, Gain: " << ShortenNumber(StrengthGain) << ") and grind until next set it ready" << std::endl;
        SetPunchingHours = SetPunchingHours * 2;
        ++Set;
    }

    if (Print) printf("\nTotal Gain: %lf\n", TotalGain);
    if (Print) std::cout << "Total Gain: " << ShortenNumber(TotalGain) << std::endl;
    return TotalGain;
}

int main()
{
    std::cout << "Pet/Aura Rebirths Glitching Speed" << std::endl;
    // change constant to change resultant set calculation
    double constant = 0;
    std::cout << "Input constant between 1-6: ";
    std::cin >> constant;
    CalculateSets(8 * 24, constant, true);
    return 0;
    /*
    double Max = 6;
    double Highest = 0;
    double iterator = 0;
    for (double i = 5; i < Max; i=i+.0000001)
    {
        double Result = CalculateSets(8 * 24, i, false);
        if (Result > Highest)
        {
            iterator = i;
            Highest = Result;
        }
    }
    std::cout << (uint64_t)Highest << " " << iterator << std::endl;
    */
    //CalculateSets(8 * 24, Highest, true);
    //CalculateSets(7 * 24, 4.9);
    //Calculate2Sets((14 * 24), (14 * 24));
    //return 0;

    /*
    uint64_t WeekHours = (8 * 24);// saturday 2pm start grinding
    uint64_t Hours = 1;
    
    uint64_t Pet = 0;
    uint64_t Aura = 0;
    uint64_t Strength = 0;
    uint64_t StrengthGain = 0;

    while (true)
    {
        Pet = ((Hours * 60 * 60) / PUNCH_TIME) * PET_ADDSTATS;
        Aura = ((Hours * 60 * 60) / PUNCH_TIME) * AURA_ADDSTATS;
        Strength = ((Pet * PETS) + Aura) * PREMIUM;
        StrengthGain = ((((WeekHours - Hours) * 60 * 60) / REP_TIME) * Strength) + (((WeekHours - Hours) * 60 * 60) / MUSCLE_KING_TIME) * Strength;

        std::cout << "Pets + Aura: " << Hours << " punching hours = " << ShortenNumber(Pet) << " & " << ShortenNumber(Aura) << " | Strength: " << ShortenNumber(Strength) << " a lift for " << (WeekHours - Hours) << " hours = " << ShortenNumber(StrengthGain) << std::endl;

        if (WeekHours - Hours <= 1)
        {
            break;
        }

        Hours = Hours + 1;
    }
    */
}
