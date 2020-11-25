

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

class Training {
public:
// Default methods for class Training
  Training(){  // Constructor
  }
  Training(const Training &EASEA_Var) {  // Copy constructor
    nb_of_students=EASEA_Var.nb_of_students;
    formation_name=EASEA_Var.formation_name;
  }
  virtual ~Training() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	EASEA_Line << this->nb_of_students << " ";
	EASEA_Line << this->formation_name << " ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	(*EASEA_Line) >> this->nb_of_students;
	(*EASEA_Line) >> this->formation_name;
  }
  Training& operator=(const Training &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    nb_of_students = EASEA_Var.nb_of_students;
    formation_name = EASEA_Var.formation_name;
  return *this;
  }

  bool operator==(Training &EASEA_Var) const {  // Operator==
    if (nb_of_students!=EASEA_Var.nb_of_students) return false;
    if (formation_name!=EASEA_Var.formation_name) return false;
  return true;
  }

  bool operator!=(Training &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const Training& EASEA_Var) { // Output stream insertion operator
    os <<  "nb_of_students:" << EASEA_Var.nb_of_students << "\n";
    os <<  "formation_name:" << EASEA_Var.formation_name << "\n";
    return os;
  }

// Class members 
  int nb_of_students;
  int formation_name;
};

class Teacher {
public:
// Default methods for class Teacher
  Teacher(){  // Constructor
  }
  Teacher(const Teacher &EASEA_Var) {  // Copy constructor
    hours_per_week=EASEA_Var.hours_per_week;
    subject=EASEA_Var.subject;
    teacher_id=EASEA_Var.teacher_id;
  }
  virtual ~Teacher() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	EASEA_Line << this->hours_per_week << " ";
	EASEA_Line << this->subject << " ";
	EASEA_Line << this->teacher_id << " ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	(*EASEA_Line) >> this->hours_per_week;
	(*EASEA_Line) >> this->subject;
	(*EASEA_Line) >> this->teacher_id;
  }
  Teacher& operator=(const Teacher &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    hours_per_week = EASEA_Var.hours_per_week;
    subject = EASEA_Var.subject;
    teacher_id = EASEA_Var.teacher_id;
  return *this;
  }

  bool operator==(Teacher &EASEA_Var) const {  // Operator==
    if (hours_per_week!=EASEA_Var.hours_per_week) return false;
    if (subject!=EASEA_Var.subject) return false;
    if (teacher_id!=EASEA_Var.teacher_id) return false;
  return true;
  }

  bool operator!=(Teacher &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const Teacher& EASEA_Var) { // Output stream insertion operator
    os <<  "hours_per_week:" << EASEA_Var.hours_per_week << "\n";
    os <<  "subject:" << EASEA_Var.subject << "\n";
    os <<  "teacher_id:" << EASEA_Var.teacher_id << "\n";
    return os;
  }

// Class members 
  int hours_per_week;
  int subject;
  int teacher_id;
};

class Course {
public:
// Default methods for class Course
  Course(){  // Constructor
  }
  Course(const Course &EASEA_Var) {  // Copy constructor
    training=EASEA_Var.training;
    room_id=EASEA_Var.room_id;
    teacher=EASEA_Var.teacher;
  }
  virtual ~Course() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
		EASEA_Line << this->training.serializer() <<" ";
	EASEA_Line << this->room_id << " ";
		EASEA_Line << this->teacher.serializer() <<" ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
		this->training.deserializer(EASEA_Line);
	(*EASEA_Line) >> this->room_id;
		this->teacher.deserializer(EASEA_Line);
  }
  Course& operator=(const Course &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    training = EASEA_Var.training;
    room_id = EASEA_Var.room_id;
    teacher = EASEA_Var.teacher;
  return *this;
  }

  bool operator==(Course &EASEA_Var) const {  // Operator==
    if (training!=EASEA_Var.training) return false;
    if (room_id!=EASEA_Var.room_id) return false;
    if (teacher!=EASEA_Var.teacher) return false;
  return true;
  }

  bool operator!=(Course &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const Course& EASEA_Var) { // Output stream insertion operator
    os <<  "training:" << EASEA_Var.training << "\n";
    os <<  "room_id:" << EASEA_Var.room_id << "\n";
    os <<  "teacher:" << EASEA_Var.teacher << "\n";
    return os;
  }

// Class members 
  Training training;
  int room_id;
  Teacher teacher;
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
  Schedule schedules[4];


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

