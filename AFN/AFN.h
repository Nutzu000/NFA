#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <queue>
class AFN {
private:
	std::vector<std::string> m_stari;
	std::string m_sigma;
	std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> m_delta;
	std::string m_stareInitiala;
	std::vector<std::string> m_finale;
public:
	AFN();
	std::vector<std::string> getStari()const;
	std::string getSigma() const;
	std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> getDelta() const;
	std::string getStareInitiala() const;
	std::vector<std::string> getFinale()const;
	void setStari(std::vector<std::string> q);
	void setSigma(const std::string& sigma);
	void setDelta(std::unordered_map<std::string, std::vector<std::pair< std::string, std::string>>> delta);
	void setStareInitiala(const std::string& q0);
	void setFinale(std::vector<std::string> f);
	void citireFisier(const std::string& fisier);
	friend std::ostream& operator<<(std::ostream& f, const AFN& afn);
	int verificare();
	std::string accepta(const std::string& cuvant);
};