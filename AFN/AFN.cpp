#include "AFN.h"
AFN::AFN() :
	m_sigma{ "" },
	m_stareInitiala{ "" }
{
}

std::vector<std::string> AFN::getStari() const
{
	return m_stari;
}

std::string AFN::getSigma() const
{
	return m_sigma;
}

std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> AFN::getDelta() const
{
	return m_delta;
}

std::string AFN::getStareInitiala() const
{
	return m_stareInitiala;
}

std::vector<std::string> AFN::getFinale() const
{
	return m_finale;
}

void AFN::setStari(std::vector<std::string> q)
{
	for (auto it : q) {
		m_stari.push_back(it);
	}
}

void AFN::setSigma(const std::string& sigma) {
	m_sigma = sigma;
}

void AFN::setDelta(std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> delta)
{
	m_delta = delta;
}

void AFN::setStareInitiala(const std::string& q0)
{
	m_stareInitiala = q0;
}

void AFN::setFinale(std::vector<std::string> f)
{
	for (auto it : f) {
		m_finale.push_back(it);
	}
}

void AFN::citireFisier(const std::string& fisier)
{
	std::ifstream f(fisier);
	std::string aux;
	std::getline(f, aux);
	std::istringstream iss(aux);
	while (iss >> aux) {
		m_stari.push_back(aux);
	}
	std::getline(f, m_sigma);
	if (m_sigma.find(" ") != std::string::npos) {
		m_sigma.replace(m_sigma.find(" "), 1, "");
	}
	f >> m_stareInitiala;
	std::getline(f, aux);
	std::getline(f, aux);
	std::istringstream iss2(aux);
	while (iss2 >> aux) {
		m_finale.push_back(aux);
	}
	std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> auxDelta;
	for (; !f.eof();) {
		std::getline(f, aux);
		std::istringstream iss(aux);
		std::string key, aux1, aux2;
		iss >> key >> aux1 >> aux2;
		auxDelta[key].push_back(std::make_pair(aux1, aux2));
	}
	this->setDelta(auxDelta);

}
int AFN::verificare()
{
	int stareaInitiala = 0;
	for (auto& it : m_stari) {
		if (it == m_stareInitiala) {
			stareaInitiala = 1;
		}
	}
	if (!stareaInitiala) {
		return 0;
	}

	int esteStareFinala = 0;
	for (auto& stareFinala : m_finale) {
		esteStareFinala = 0;
		for (auto& it : m_stari) {
			if (it == stareFinala) {
				esteStareFinala = 1;
				break;
			}
		}
		if (!esteStareFinala) {
			return 0;
		}
	}

	for (auto& key : m_delta) {
		int existaCheie = 0;
		for (auto& stari : m_stari) {
			if (key.first==stari) {
				existaCheie = 1;
			}
		}
		if (!existaCheie) {
			return 0;
		}
		for (auto& it : key.second) {
			if (m_sigma.find(std::get<0>(it)) == std::string::npos) {
				return 0;
			}
			int existaStareDeTranzitie = 0;
			for (auto& stari : m_stari) {
				if (std::get<1>(it) == stari|| std::get<1>(it) == "vid") {
					existaStareDeTranzitie = 1;
				}
			}
			if (!existaStareDeTranzitie) {
				return 0;
			}
		}
	}
	return 1;
}
std::string AFN::accepta(const std::string& cuvant)
{
	std::queue<std::pair<std::string, std::string>> coada;
	coada.push(std::make_pair(cuvant, m_stareInitiala));
	while (!coada.empty()) {
		if (coada.front().first == "") {
			for (auto& stareFinala : m_finale) {
				if (stareFinala == coada.front().second) {
					return "ACCEPTAT";
				}
			}
			coada.pop();
		}
		else {
			std::string simbol= coada.front().first.substr(0,1);
			for (auto& it : m_delta[coada.front().second]) {
				if (it.first == simbol) {
					coada.push(
						std::make_pair(
							coada.front().first.substr(1, coada.front().first.length()),
								it.second
							)
						);
				}
			}
			coada.pop();
		}
	}
	return "NEACCEPTAT";
}
std::ostream& operator<<(std::ostream& f, const AFN& afn)
{
	std::cout << "AFN={\n"
		<< "Stari:\n";
	for (auto& it : afn.getStari()) {
		std::cout << it << ' ';
	}
	std::cout << "\nSigma:\n";
	for (auto& it : afn.getSigma()) {
		std::cout << it << ' ';
	}

	std::cout << "\nStarea initiala:\n" << afn.getStareInitiala()
		<< "\nStarile finale:\n";
	for (auto it : afn.getFinale()) {
		std::cout << it << ' ';
	}
	std::cout << "\nDelta:\n";
	for (auto& key : afn.getDelta()) {
		for (auto& it : key.second) {
			std::cout << key.first << ' ' << std::get<0>(it) << ' ' << std::get<1>(it);
			std::cout << "\n";
		}
	}
	std::cout << "}\n";
	return f;
}
