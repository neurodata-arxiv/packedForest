#ifndef fpForestClassification_h
#define fpForestClassification_h
//#include "../baseFunctions/fpForestBase.h"
#include "../baseFunctions/fpUtils.h"
#include <vector>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include "rfTree.h"

namespace fp {

	template <typename T>
		class fpForestClassificationBase : public fpForestBase
	{
		protected:
			std::vector<rfTree<T> > trees;

		public:
			fpForestClassificationBase(){
				std::srand(unsigned(std::time(0)));
			}

			void printForestType(){
				std::cout << "This is a basic classification forest.\n";
			}

			void changeForestSize(){
				trees.resize(fpSingleton::getSingleton().returnNumTrees());
			}

			void growTrees(){
				for(auto &tree : trees){
					tree.growTree();
					//std::cout << "OOB: " <<	tree.returnOOB() << "\n";
				}
			}

			inline void checkParameters(){
				;
			}

			void growForest(){
				//	checkParameters();
				changeForestSize();
				growTrees();
			}

			int predictClass(int observationNumber){
			//	return 0;
				
				std::vector<int> classTally(fpSingleton::getSingleton().returnNumClasses(),0);
				for(int i = 0; i < fpSingleton::getSingleton().returnNumTrees(); ++i){
++classTally[trees[i].predictObservation(observationNumber)];
				}

				int bestClass = 0;
			//	for(int i : classTally){
			//	std::cout << i << ", ";
			//	}
			//	std::cout << "\n";
				for(int j = 1; j < fpSingleton::getSingleton().returnNumClasses(); ++j){
					if(classTally[bestClass] < classTally[j]){
						bestClass = j;
					}
				}
				return bestClass;
			}

			float testForest(){
				float numTried = 0;
				float numWrong = 0;

				for (int i = 0; i <fpSingleton::getSingleton().returnNumObservations();i++){
					++numTried;
					int predClass = predictClass(i);
					if(predClass != fpSingleton::getSingleton().returnTestLabel(i)){
						++numWrong;
//						std::cout << predClass << ":" << fpSingleton::getSingleton().returnTestLabel(i) << "\n";
					}
				}

				return numWrong/numTried;
			}
	};

}// namespace fp
#endif //fpForestClassification_h