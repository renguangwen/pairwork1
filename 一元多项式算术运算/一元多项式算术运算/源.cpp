#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
struct PolynomialTerm {
    float coefficient; // ϵ��
    int power; // ����
};

typedef std::vector<PolynomialTerm> Polynomial; // ����ʽ���Ͷ���Ϊһ��vector�ṹ

bool cmp(const PolynomialTerm& a, const PolynomialTerm& b) { // ������
    return a.power > b.power;
}

void inputPolynomial(Polynomial& poly, std::string fileName) {
    std::cout << "���������ʽ������:" << std::endl;
    int termCount;
    std::cin >> termCount;

    while (termCount <= 0) {
        std::cout << "���������������������0��������" << std::endl;
        std::cin >> termCount;
    }

    for (int i = 0; i < termCount; i++) {
        std::cout << "�������" << i + 1 << "���ϵ���ʹ���:" << std::endl;
        PolynomialTerm term;
        std::cin >> term.coefficient >> term.power;
        poly.push_back(term);
    }

    std::ofstream outFile(fileName.c_str()); // д���ļ�
    outFile << termCount << std::endl;
    for (int i = 0; i < poly.size(); i++) {
        outFile << poly[i].coefficient << " " << poly[i].power << std::endl;
    }
    outFile.close();
}

void outputPolynomial(const Polynomial& poly, std::string fileName) {
    std::ofstream outFile(fileName.c_str()); // д���ļ�
    outFile << poly.size() << std::endl;
    for (int i = 0; i < poly.size(); i++) {
        outFile << poly[i].coefficient << " " << poly[i].power << std::endl;
    }
    outFile.close();
}

Polynomial addPolynomial(const Polynomial& poly1, const Polynomial& poly2) {//�ӷ�����
    Polynomial result;
    int i = 0, j = 0;

    while (i < poly1.size() && j < poly2.size()) {
        if (poly1[i].power > poly2[j].power) {
            result.push_back(poly1[i++]);
        }
        else if (poly1[i].power < poly2[j].power) {
            result.push_back(poly2[j++]);
        }
        else {
            PolynomialTerm term;
            term.coefficient = poly1[i].coefficient + poly2[j].coefficient;
            term.power = poly1[i].power;
            result.push_back(term);
            i++;
            j++;
        }
    }

    while (i < poly1.size()) {
        result.push_back(poly1[i++]);
    }

    while (j < poly2.size()) {
        result.push_back(poly2[j++]);
    }

    sort(result.begin(), result.end(), cmp); // ��result����ָ����С��������

    Polynomial newResult; // �ϲ�ͬ����
    int size = result.size();
    for (int i = 0; i < size; i++) {
        PolynomialTerm term;
        term.coefficient = result[i].coefficient;
        term.power = result[i].power;
        for (int j = i + 1; j < size; j++) {
            if (result[j].power == result[i].power) {
                term.coefficient += result[j].coefficient;
                i++;
            }
            else {
                break;
            }
        }
        newResult.push_back(term);
    }
    return newResult;
}

Polynomial subPolynomial(const Polynomial& poly1, const Polynomial& poly2) {//��������
    Polynomial result;
    int i = 0, j = 0;

    while (i < poly1.size() && j < poly2.size()) {
        if (poly1[i].power > poly2[j].power) {
            result.push_back(poly1[i++]);
        }
        else if (poly1[i].power < poly2[j].power) {
            PolynomialTerm term;
            term.coefficient = -1 * poly2[j].coefficient;
            term.power = poly2[j].power;
            result.push_back(term);
            j++;
        }
        else {
            PolynomialTerm term;
            term.coefficient = poly1[i].coefficient - poly2[j].coefficient;
            term.power = poly1[i].power;
            result.push_back(term);
            i++;
            j++;
        }
    }
    while (i < poly1.size()) {
        result.push_back(poly1[i++]);
    }

    while (j < poly2.size()) {
        PolynomialTerm term;
        term.coefficient = -1 * poly2[j].coefficient;
        term.power = poly2[j].power;
        result.push_back(term);
        j++;
    }

    sort(result.begin(), result.end(), cmp); // ��result����ָ����С��������

    Polynomial newResult; // �ϲ�ͬ����
    int size = result.size();
    for (int i = 0; i < size; i++) {
        PolynomialTerm term;
        term.coefficient = result[i].coefficient;
        term.power = result[i].power;
        for (int j = i + 1; j < size; j++) {
            if (result[j].power == result[i].power) {
                term.coefficient += result[j].coefficient;
                i++;
            }
            else {
                break;
            }
        }
        newResult.push_back(term);
    }
    return newResult;
}

void printPolynomial(const Polynomial& poly) {
    for (int i = 0; i < poly.size(); i++) {
        if (poly[i].coefficient != 0) { // �ų�ϵ��Ϊ0����
            if (i > 0 && poly[i].coefficient > 0) {
                std::cout << "+ ";
            }
            std::cout << poly[i].coefficient;
            if (poly[i].power != 0) {
                std::cout << "x";
                if (poly[i].power != 1) {
                    std::cout << "^" << poly[i].power;
                }
            }
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    Polynomial poly1, poly2;
    std::string fileName1 = "poly1.txt";
    std::string fileName2 = "poly2.txt";

    inputPolynomial(poly1, fileName1);
    inputPolynomial(poly2, fileName2);

    Polynomial resultAdd = addPolynomial(poly1, poly2);
    Polynomial resultSub = subPolynomial(poly1, poly2);

    std::cout << "����ʽ1Ϊ��";
    printPolynomial(poly1);
    std::cout << "����ʽ2Ϊ��";
    printPolynomial(poly2);
    std::cout << "����ʽ��ӽ��Ϊ��";
    printPolynomial(resultAdd);
    std::cout << "����ʽ������Ϊ��";
    printPolynomial(resultSub);
    outputPolynomial(resultAdd, "result1.txt");
    outputPolynomial(resultSub, "result2.txt");
    return 0;
}