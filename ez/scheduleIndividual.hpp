

#ifndef PROBLEM_DEP_H
#define PROBLEM_DEP_H

//#include "CRandomGenerator.h"
#include <stdlib.h>
#include <iostream>
#include <CIndividual.h>
#include <Parameters.h>
#include <cstring>
#include <sstream>

using namespace std;

class CRandomGenerator;
class CSelectionOperator;
class CGenerationalCriterion;
class CEvolutionaryAlgorithm;
class CPopulation;
class Parameters;

extern int EZ_POP_SIZE;
extern int OFFSPRING_SIZE;

// User classes

class Course {
public:
// Default methods for class Course
  Course(){  // Constructor
  }
  Course(const Course &EASEA_Var) {  // Copy constructor
    room_id=EASEA_Var.room_id;
    teacher_id=EASEA_Var.teacher_id;
    subject=EASEA_Var.subject;
  }
  virtual ~Course() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	EASEA_Line << this->room_id << " ";
	EASEA_Line << this->teacher_id << " ";
	EASEA_Line << this->subject << " ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	(*EASEA_Line) >> this->room_id;
	(*EASEA_Line) >> this->teacher_id;
	(*EASEA_Line) >> this->subject;
  }
  Course& operator=(const Course &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    room_id = EASEA_Var.room_id;
    teacher_id = EASEA_Var.teacher_id;
    subject = EASEA_Var.subject;
  return *this;
  }

  bool operator==(Course &EASEA_Var) const {  // Operator==
    if (room_id!=EASEA_Var.room_id) return false;
    if (teacher_id!=EASEA_Var.teacher_id) return false;
    if (subject!=EASEA_Var.subject) return false;
  return true;
  }

  bool operator!=(Course &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const Course& EASEA_Var) { // Output stream insertion operator
    os <<  "room_id:" << EASEA_Var.room_id << "\n";
    os <<  "teacher_id:" << EASEA_Var.teacher_id << "\n";
    os <<  "subject:" << EASEA_Var.subject << "\n";
    return os;
  }

// Class members 
  int room_id;
  int teacher_id;
  int subject;
};

class Schedule {
public:
// Default methods for class Schedule
  Schedule(){  // Constructor
  }
  Schedule(const Schedule &EASEA_Var) {  // Copy constructor
    {for(int EASEA_Ndx=0; EASEA_Ndx<10; EASEA_Ndx++)
       courses[EASEA_Ndx]=EASEA_Var.courses[EASEA_Ndx];}
  }
  virtual ~Schedule() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	for(int EASEA_Ndx=0; EASEA_Ndx<10; EASEA_Ndx++)
		EASEA_Line << this->courses[EASEA_Ndx].serializer() <<" ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	for(int EASEA_Ndx=0; EASEA_Ndx<10; EASEA_Ndx++)
		this->courses[EASEA_Ndx].deserializer(EASEA_Line) ;
  }
  Schedule& operator=(const Schedule &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    {for(int EASEA_Ndx=0; EASEA_Ndx<10; EASEA_Ndx++)
       courses[EASEA_Ndx] = EASEA_Var.courses[EASEA_Ndx];}
  return *this;
  }

  bool operator==(Schedule &EASEA_Var) const {  // Operator==
    {for(int EASEA_Ndx=0; EASEA_Ndx<10; EASEA_Ndx++)
       if (courses[EASEA_Ndx]!=EASEA_Var.courses[EASEA_Ndx]) return false;}
  return true;
  }

  bool operator!=(Schedule &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const Schedule& EASEA_Var) { // Output stream insertion operator
    {os << "Array courses : ";
     for(int EASEA_Ndx=0; EASEA_Ndx<10; EASEA_Ndx++)
       os << "[" << EASEA_Ndx << "]:" << EASEA_Var.courses[EASEA_Ndx] << "\t";}
    os << "\n";
    return os;
  }

// Class members 
  Course courses[10];
};


class IndividualImpl : public CIndividual {

public: // in schedule the genome is public (for user functions,...)
	// Class members
  	// Class members 
  Schedule *schedules;


public:
	IndividualImpl();
	IndividualImpl(const IndividualImpl& indiv);
	virtual ~IndividualImpl();
	float evaluate();
	static unsigned getCrossoverArrity(){ return 2; }
	float getFitness(){ return this->fitness; }
	CIndividual* crossover(CIndividual** p2);
	void printOn(std::ostream& O) const;
	CIndividual* clone();

	void mutate(float pMutationPerGene);

	void boundChecking();      

	string serialize();
	void deserialize(string EASEA_Line);

	friend std::ostream& operator << (std::ostream& O, const IndividualImpl& B) ;
	void initRandomGenerator(CRandomGenerator* rg){ IndividualImpl::rg = rg;}

};


class ParametersImpl : public Parameters {
public:
	void setDefaultParameters(int argc, char** argv);
	CEvolutionaryAlgorithm* newEvolutionaryAlgorithm();
};

/**
 * @TODO ces functions devraient s'appeler weierstrassInit, weierstrassFinal etc... (en gros scheduleFinal dans le tpl).
 *
 */

void scheduleInit(int argc, char** argv);
void scheduleFinal(CPopulation* pop);
void scheduleBeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm);
void scheduleEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm);
void scheduleGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm);


class EvolutionaryAlgorithmImpl: public CEvolutionaryAlgorithm {
public:
	EvolutionaryAlgorithmImpl(Parameters* params);
	virtual ~EvolutionaryAlgorithmImpl();
	void initializeParentPopulation();
};

#endif /* PROBLEM_DEP_H */

