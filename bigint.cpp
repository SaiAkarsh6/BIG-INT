#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class BIGINT {
private:
    string value;
    bool isNegative;

    void removeLeadingZeros() {
        while (value.size() > 1 && value[0] == '0') {
            value.erase(value.begin());
        }
        if (value == "0") {
            isNegative = false;
        }
    }

    string addStrings(const string &num1, const string &num2) const {
        string result;
        int carry = 0, sum = 0;

        int i = num1.size() - 1, j = num2.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
            int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
            sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }
        reverse(result.begin(), result.end());
        return result;
    }

    string subtractStrings(const string &num1, const string &num2) const {
        string result;
        int borrow = 0;

        int i = num1.size() - 1, j = num2.size() - 1;
        while (i >= 0 || j >= 0) {
            int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
            int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
            int diff = digit1 - digit2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(diff + '0');
        }
        reverse(result.begin(), result.end());
        return result;
    }

public:
    BIGINT() : value("0"), isNegative(false) {}
    BIGINT(const string &str) {
        if (str[0] == '-') {
            isNegative = true;
            value = str.substr(1);
        } else {
            isNegative = false;
            value = str;
        }
        removeLeadingZeros();
    }

    BIGINT operator+(const BIGINT &other) const {
        if (isNegative == other.isNegative) {
            BIGINT result;
            result.value = addStrings(value, other.value);
            result.isNegative = isNegative;
            return result;
        } else {
            if (value == other.value) {
                return BIGINT("0");
            } else if (value > other.value) {
                BIGINT result;
                result.value = subtractStrings(value, other.value);
                result.isNegative = isNegative;
                return result;
            } else {
                BIGINT result;
                result.value = subtractStrings(other.value, value);
                result.isNegative = other.isNegative;
                return result;
            }
        }
    }

    BIGINT operator-(const BIGINT &other) const {
        BIGINT negOther = other;
        negOther.isNegative = !other.isNegative;
        return *this + negOther;
    }

    friend ostream &operator<<(ostream &out, const BIGINT &num) {
        if (num.isNegative) {
            out << '-';
        }
        out << num.value;
        return out;
    }
};

int main() {
    // Input/output for a competitive programming problem
    string a, b;
    cin >> a >> b;

    BIGINT num1(a);
    BIGINT num2(b);

    cout << "Sum: " << (num1 + num2) << endl;
    cout << "Difference: " << (num1 - num2) << endl;

    return 0;
}
