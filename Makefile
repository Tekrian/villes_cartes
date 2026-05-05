# ============================================================
# Makefile - Projet Temps de Route
# ============================================================
# Utilisation :
#   make        → compile tout et produit prog.exe
#   make clean  → supprime les fichiers compilés
# ============================================================
#g++ -Wall -Wfatal-errors -c Polynome.cpp


CXX=g++
CXXFLAGS=-Wall -I include   # -I include : cherche les .hpp dans include/

TARGET = prog.exe

# ============================================================
# Règle principale : lie tous les .o pour produire prog.exe
# ============================================================
$(TARGET): main.o Graph.o Ville.o CsvLoader.o
	$(CXX) -o $(TARGET) main.o Graph.o Ville.o CsvLoader.o

# ============================================================
# Règles de compilation
# Chaque .cpp est compilé en .o séparément (-c)
# On précise les .hpp dont dépend chaque fichier
# ============================================================

main.o: src/main.cpp include/Graph.hpp include/Ville.hpp include/CsvLoader.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp

Graph.o: src/Graph.cpp include/Graph.hpp
	$(CXX) $(CXXFLAGS) -c src/Graph.cpp

Ville.o: src/Ville.cpp include/Ville.hpp
	$(CXX) $(CXXFLAGS) -c src/Ville.cpp

CsvLoader.o: src/CsvLoader.cpp include/CsvLoader.hpp include/Graph.hpp include/Ville.hpp
	$(CXX) $(CXXFLAGS) -c src/CsvLoader.cpp

# ============================================================
# Nettoyage des fichiers générés
# ============================================================
clean:
	rm -f *.o $(TARGET)