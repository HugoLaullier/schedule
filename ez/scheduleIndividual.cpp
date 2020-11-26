

#include <fstream>
#include <time.h>
#include <cstring>
#include <sstream>
#include "CRandomGenerator.h"
#include "CPopulation.h"
#include "COptionParser.h"
#include "CStoppingCriterion.h"
#include "CEvolutionaryAlgorithm.h"
#include "global.h"
#include "CIndividual.h"

using namespace std;
bool bReevaluate = false;
typedef float TO;
typedef float TV;

#include "scheduleIndividual.hpp"
bool INSTEAD_EVAL_STEP = false;


CRandomGenerator* globalRandomGenerator;
extern CEvolutionaryAlgorithm* EA;
#define STD_TPL


// User declarations
#line 6 "ez/schedule.ez"

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/istreamwrapper.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"
#include <fstream>
#include <iostream>
#include <vector>
#define NB_SCHEDULES 4
#define NB_COURSES 10

enum subject_t {
    MATHEMATICS, 
    PHYSICS, 
    COMPUTER_SCIENCE,
    ENGLISH
};

enum room_type_t {
    TP,
    TD,
    LABO
};

enum formation_name_t {MI, PI};

Teacher* teachers;
Room* rooms;
Promotion* promotions;
Training* trainings;





// User functions

#line 40 "ez/schedule.ez"

int getData()
{
  ifstream ifs("../json/in/data.json");
  if (!ifs.is_open())
  {
      std::cerr << "Could not open file for reading!\n";
      return EXIT_FAILURE;
  }

  rapidjson::IStreamWrapper isw(ifs);

  rapidjson::Document doc{};
  doc.ParseStream(isw);

  teachers = (Teacher *) malloc(doc["teachers"].Size()*sizeof(Teacher));

  for (rapidjson::SizeType i = 0; i < doc["teachers"].Size(); i++)
  {
      Teacher teacher;
      teacher.id = i;
      if(doc["teachers"][i]["subject"] == "Mathematics")
        teacher.subject = MATHEMATICS;
        else if(doc["teachers"][i]["subject"] == "Physics")
        teacher.subject = PHYSICS;
        else if(doc["teachers"][i]["subject"] == "Computer Science")
        teacher.subject = COMPUTER_SCIENCE;
        else if(doc["teachers"][i]["subject"] == "English")
        teacher.subject = ENGLISH;
        else
            std::cerr << doc["teachers"][i]["subject"].GetString() << " is not a subject" << std::endl;
      teacher.hours_per_week = doc["teachers"][i]["hours_per_week"].GetInt();

      teachers[i] = teacher;      
  }

  rooms = (Room *) malloc(doc["rooms"].Size()*sizeof(Teacher));
  for (rapidjson::SizeType i = 0; i < doc["rooms"].Size(); i++)
  {
      Room room;
      room.id = i;
      if(doc["rooms"][i]["type"] == "TP")
        room.type = TP;
        else if(doc["rooms"][i]["type"] == "TD")
        room.type = TD;
        else if(doc["rooms"][i]["type"] == "labo")
        room.type = LABO;
        else
            std::cerr << doc["rooms"][i]["type"].GetString() << " is not a type of room" << std::endl;
      room.places = doc["rooms"][i]["places"].GetInt();

      rooms[i] = room;      
  }

  promotions = (Promotion *) malloc(doc["promotions"].Size()*sizeof(Promotion));
  for (rapidjson::SizeType i = 0; i < doc["promotions"].Size(); i++)
  {
      Promotion promotion;
      promotion.id = i;
      if(doc["promotions"][i]["training"] == "MI")
        promotion.type = MI;
        else if(doc["promotions"][i]["training"] == "PI")
        promotion.type = PI;
        else
            std::cerr << doc["promotions"][i]["training"].GetString() << " is not a training" << std::endl;
      promotion.places = doc["promotions"][i]["nb_of_students"].GetInt();

      promotions[i] = promotion;      
  }

  trainings = (Training *) malloc(doc["trainings"].Size()*sizeof(Training));
  for (rapidjson::SizeType i = 0; i < doc["trainings"].Size(); i++)
  {
      Promotion promotion;
      if(doc["trainings"][i]["name"] == "MI")
        promotion.type = MI;
        else if(doc["trainings"][i]["name"] == "PI")
        promotion.type = PI;
        else
            std::cerr << doc["trainings"][i]["name"].GetString() << " is not a training" << std::endl;
      Subject* subjects = (Subject *) malloc(doc["trainings"][i]["subjects"].Size()*sizeof(Subject));
      for (rapidjson::SizeType j = 0; j < doc["trainings"][i]["subjects"].Size(); j++)
      {
          Subject subject;
          if(doc["trainings"][i]["subjects"][j]["name"] == "Mathematics")
        subject.name = MATHEMATICS;
        else if(doc["trainings"][i]["subjects"][j]["name"] == "Physics")
        subject.name = PHYSICS;
        else if(doc["trainings"][i]["subjects"][j]["name"] == "Computer Science")
        subject.name = COMPUTER_SCIENCE;
        else if(doc["trainings"][i]["subjects"][j]["name"] == "English")
        subject.name = ENGLISH;
        else
            std::cerr << doc["trainings"][i]["subjects"][j]["name"].GetString() << " is not a subject" << std::endl;
        subjects[i]=subject
      }

      promotion[i].subjects = subjects;

      promotions[i] = promotion;      
  }



}


// Initialisation function
void EASEAInitFunction(int argc, char *argv[]){
#line 149 "ez/schedule.ez"

getData();
}

// Finalization function
void EASEAFinalization(CPopulation* population){
#line 153 "ez/schedule.ez"

}



void evale_pop_chunk(CIndividual** population, int popSize){
  
// No Instead evaluation step function.

}

void scheduleInit(int argc, char** argv){
	
  EASEAInitFunction(argc, argv);

}

void scheduleFinal(CPopulation* pop){
	
  EASEAFinalization(pop);
;
}

void EASEABeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	#line 264 "ez/schedule.ez"
{
#line 156 "ez/schedule.ez"

}
}

void EASEAEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

}
}

void EASEAGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

}
}


IndividualImpl::IndividualImpl() : CIndividual() {
      schedules=NULL;
 
  // Genome Initialiser
#line 216 "ez/schedule.ez"
 

  valid = false;
  isImmigrant = false;
}

CIndividual* IndividualImpl::clone(){
	return new IndividualImpl(*this);
}

IndividualImpl::~IndividualImpl(){
  // Destructing pointers
  if (schedules) delete schedules;
  schedules=NULL;

}


float IndividualImpl::evaluate(){
  if(valid)
    return fitness;
  else{
    valid = true;
    #line 226 "ez/schedule.ez"
 // Returns the score

  }
}

void IndividualImpl::boundChecking(){
	
// No Bound checking function.

}

string IndividualImpl::serialize(){
    ostringstream EASEA_Line(ios_base::app);
    // Memberwise serialization
	if(this->schedules != NULL){
		EASEA_Line << "\a ";
		EASEA_Line << this->schedules->serializer() << " ";
	}
	else
		EASEA_Line << "NULL" << " ";

    EASEA_Line << this->fitness;
    return EASEA_Line.str();
}

void IndividualImpl::deserialize(string Line){
    istringstream EASEA_Line(Line);
    string line;
    // Memberwise deserialization
	EASEA_Line >> line;
	if(strcmp(line.c_str(),"NULL")==0)
		this->schedules = NULL;
	else{
		this->schedules = new Schedule;
		this->schedules->deserializer(&EASEA_Line);
	}
    EASEA_Line >> this->fitness;
    this->valid=true;
    this->isImmigrant = false;
}

IndividualImpl::IndividualImpl(const IndividualImpl& genome){

  // ********************
  // Problem specific part
  // Memberwise copy
    schedules=(genome.schedules ? new Schedule(*(genome.schedules)) : NULL);



  // ********************
  // Generic part
  this->valid = genome.valid;
  this->fitness = genome.fitness;
  this->isImmigrant = false;
}


CIndividual* IndividualImpl::crossover(CIndividual** ps){
	// ********************
	// Generic part
	IndividualImpl** tmp = (IndividualImpl**)ps;
	IndividualImpl parent1(*this);
	IndividualImpl parent2(*tmp[0]);
	IndividualImpl child(*this);

	//DEBUG_PRT("Xover");
	/*   cout << "p1 : " << parent1 << endl; */
	/*   cout << "p2 : " << parent2 << endl; */

	// ********************
	// Problem specific part
  	#line 219 "ez/schedule.ez"

// create child (initialized to parent1) out of parent1 and parent2 



	child.valid = false;
	/*   cout << "child : " << child << endl; */
	return new IndividualImpl(child);
}


void IndividualImpl::printOn(std::ostream& os) const{
	

}

std::ostream& operator << (std::ostream& O, const IndividualImpl& B)
{
  // ********************
  // Problem specific part
  O << "\nIndividualImpl : "<< std::endl;
  O << "\t\t\t";
  B.printOn(O);

  if( B.valid ) O << "\t\t\tfitness : " << B.fitness;
  else O << "fitness is not yet computed" << std::endl;
  return O;
}


void IndividualImpl::mutate( float pMutationPerGene ){
  this->valid=false;


  // ********************
  // Problem specific part
  #line 223 "ez/schedule.ez"
 // all the values in here are found by trial and error

}

void ParametersImpl::setDefaultParameters(int argc, char** argv){

	this->minimizing = true;
	this->nbGen = setVariable("nbGen",(int)100);
	this->nbCPUThreads = setVariable("nbCPUThreads", 1);
	this->reevaluateImmigrants = setVariable("reevaluateImmigrants", 0);

	omp_set_num_threads(this->nbCPUThreads);
	seed = setVariable("seed",(int)time(0));
	globalRandomGenerator = new CRandomGenerator(seed);
	this->randomGenerator = globalRandomGenerator;


	selectionOperator = getSelectionOperator(setVariable("selectionOperator","Tournament"), this->minimizing, globalRandomGenerator);
	replacementOperator = getSelectionOperator(setVariable("reduceFinalOperator","Tournament"),this->minimizing, globalRandomGenerator);
	parentReductionOperator = getSelectionOperator(setVariable("reduceParentsOperator","Tournament"),this->minimizing, globalRandomGenerator);
	offspringReductionOperator = getSelectionOperator(setVariable("reduceOffspringOperator","Tournament"),this->minimizing, globalRandomGenerator);
	selectionPressure = setVariable("selectionPressure",(float)10.000000);
	replacementPressure = setVariable("reduceFinalPressure",(float)7.000000);
	parentReductionPressure = setVariable("reduceParentsPressure",(float)2.000000);
	offspringReductionPressure = setVariable("reduceOffspringPressure",(float)2.000000);
	pCrossover = 1.000000;
	pMutation = 1.000000;
	pMutationPerGene = 0.05;

	parentPopulationSize = setVariable("popSize",(int)4096);
	offspringPopulationSize = setVariable("nbOffspring",(int)4096);


	parentReductionSize = setReductionSizes(parentPopulationSize, setVariable("survivingParents",(float)1.000000));
	offspringReductionSize = setReductionSizes(offspringPopulationSize, setVariable("survivingOffspring",(float)1.000000));

	this->elitSize = setVariable("elite",(int)1);
	this->strongElitism = setVariable("eliteType",(int)0);

	if((this->parentReductionSize + this->offspringReductionSize) < this->parentPopulationSize){
		printf("*WARNING* parentReductionSize + offspringReductionSize < parentPopulationSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if((this->parentPopulationSize-this->parentReductionSize)>this->parentPopulationSize-this->elitSize){
		printf("*WARNING* parentPopulationSize - parentReductionSize > parentPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if(!this->strongElitism && ((this->offspringPopulationSize - this->offspringReductionSize)>this->offspringPopulationSize-this->elitSize)){
		printf("*WARNING* offspringPopulationSize - offspringReductionSize > offspringPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	

	/*
	 * The reduction is set to true if reductionSize (parent or offspring) is set to a size less than the
	 * populationSize. The reduction size is set to populationSize by default
	 */
	if(offspringReductionSize<offspringPopulationSize) offspringReduction = true;
	else offspringReduction = false;

	if(parentReductionSize<parentPopulationSize) parentReduction = true;
	else parentReduction = false;

	generationalCriterion = new CGenerationalCriterion(setVariable("nbGen",(int)100));
	controlCStopingCriterion = new CControlCStopingCriterion();
	timeCriterion = new CTimeCriterion(setVariable("timeLimit",0));

	this->optimise = 0;

	this->printStats = setVariable("printStats",1);
	this->generateCSVFile = setVariable("generateCSVFile",0);
	this->generatePlotScript = setVariable("generatePlotScript",0);
	this->generateRScript = setVariable("generateRScript",0);
	this->plotStats = setVariable("plotStats",1);
	this->printInitialPopulation = setVariable("printInitialPopulation",0);
	this->printFinalPopulation = setVariable("printFinalPopulation",0);
	this->savePopulation = setVariable("savePopulation",0);
	this->startFromFile = setVariable("startFromFile",0);

	this->outputFilename = (char*)"schedule";
	this->plotOutputFilename = (char*)"schedule.png";

	this->remoteIslandModel = setVariable("remoteIslandModel",1);
	std::string* ipFilename=new std::string();
	*ipFilename=setVariable("ipFile","ip.txt");

	this->ipFile =(char*)ipFilename->c_str();
	this->migrationProbability = setVariable("migrationProbability",(float)0.333000);
    this->serverPort = setVariable("serverPort",2929);
}

CEvolutionaryAlgorithm* ParametersImpl::newEvolutionaryAlgorithm(){

	pEZ_MUT_PROB = &pMutationPerGene;
	pEZ_XOVER_PROB = &pCrossover;
	//EZ_NB_GEN = (unsigned*)setVariable("nbGen",100);
	EZ_current_generation=0;
  EZ_POP_SIZE = parentPopulationSize;
  OFFSPRING_SIZE = offspringPopulationSize;

	CEvolutionaryAlgorithm* ea = new EvolutionaryAlgorithmImpl(this);
	generationalCriterion->setCounterEa(ea->getCurrentGenerationPtr());
	ea->addStoppingCriterion(generationalCriterion);
	ea->addStoppingCriterion(controlCStopingCriterion);
	ea->addStoppingCriterion(timeCriterion);	

	EZ_NB_GEN=((CGenerationalCriterion*)ea->stoppingCriteria[0])->getGenerationalLimit();
	EZ_current_generation=&(ea->currentGeneration);

	 return ea;
}

void EvolutionaryAlgorithmImpl::initializeParentPopulation(){
	if(this->params->startFromFile){
	  ifstream EASEA_File("schedule.pop");
	  string EASEA_Line;
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
	  	  getline(EASEA_File, EASEA_Line);
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
		  ((IndividualImpl*)this->population->parents[i])->deserialize(EASEA_Line);
	  }
	  
	}
	else{
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
	  }
	}
        this->population->actualParentPopulationSize = this->params->parentPopulationSize;
}


EvolutionaryAlgorithmImpl::EvolutionaryAlgorithmImpl(Parameters* params) : CEvolutionaryAlgorithm(params){
	;
}

EvolutionaryAlgorithmImpl::~EvolutionaryAlgorithmImpl(){

}

