#include <iostream>
#include <string>
#include "CitizensDB.h"
#include "District.h"
#include "DistrictsArr.h"
#include "CitizensArr.h"
#include "PartiesArr.h"
#include "UserActions.h"
#include <algorithm>

using namespace std;
using namespace elections;

// ( 1 )
// This function creates new district and adds it to districtsArr.
void addNewDistrict(DistrictsArr& districtsArr, PartiesArr& partiesArr, CitizensDB& citizensDB);
// ( 2 )
// This function creates new citizen and adds it to citizensArr.
void addNewCitizen(CitizensDB& citizensDB, DistrictsArr& districtsArr);
// ( 3)
// This function creates new party and adds it to districtsArr.
void addNewParty(PartiesArr& partiesArr, DistrictsArr& districtsArr, CitizensDB& citizensDB);
// ( 4 )
// This function creates new rep and adds it to repsArr inside partiesArr.
void addNewRep(PartiesArr& partiesArr, CitizensDB& citizensDB, DistrictsArr& districtsArr);

// This function gets name and returns it's length.
int getStrLen(char* name);

// This function lets' the user vote by inputting citizen id and party, 
// and adds the vote to the party inside partiesArr.
void addNewVote(CitizensArr& citizensArr, PartiesArr& partiesArr);

void printMenu();

int main() {
	UserActions userActions;
	int action = 0;

	DistrictsArr districtsArr;
	CitizensDB citizensDB;
	PartiesArr partiesArr;

	printMenu();

	while (action != 10) {
		cin >> action;
		userActions = (UserActions)action;

		switch (userActions) {
		case UserActions::ADD_DISTRICT:
			addNewDistrict(districtsArr, partiesArr, citizensDB);
			break;

		case UserActions::ADD_CITIZEN:
			addNewCitizen(citizensDB, districtsArr);
			break;

		case UserActions::ADD_PARTY:
			addNewParty(partiesArr, districtsArr, citizensDB);
			break;

		case UserActions::ADD_REP:
			addNewRep(partiesArr, citizensDB, districtsArr);
			break;

		case UserActions::SHOW_ALL_DISTRICTS:
			cout << districtsArr;
			break;

		case UserActions::SHOW_ALL_CITIZENS:
			cout << citizensDB;
			break;

		case UserActions::SHOW_ALL_PARTIES:
			cout << partiesArr;
			break;

		case UserActions::VOTE:
			//addNewVote(citizensDB, partiesArr);
			break;

		case UserActions::SHOW_ELECTION_POLLS:
			//countVotes(districtsArr, citizensArr, partiesArr);
			break;

		case UserActions::EXIT:
			cout << "Goodbye." << endl;
			break;

		default:
			cout << "NO INPUT" << endl;
			break;
		}
	}
}

// ( 1 )
void addNewDistrict(DistrictsArr& districtsArr, PartiesArr& partiesArr, CitizensDB& citizensDB) {
	char name[20];
	int nameLen, numOfRep;

	cout << "Enter district name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	if (!districtsArr.isDistrictExistsByName((name))) {

		nameLen = getStrLen(name);

		cout << "Enter number of representatives: ";
		cin >> numOfRep;

		District newDist(name, nameLen, numOfRep, districtsArr.getLogSize());

		districtsArr.add(newDist);

		citizensDB.addEmptyCitizensArr(); // adding new citizensArr in DB for new district
		partiesArr.addNewDistToRepArr(); //// adding new citizensArr to reps list of each party for new district 
	}
	else
		cout << "The district with name " << name << " already exists!!!" << endl;


}
// ( 2 )
void addNewCitizen(CitizensDB& citizensDB, DistrictsArr& districtsArr)
{
	char name[20];
	int nameLen, districtNum, year;
	long int id;

	cout << "Enter citizen's name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	nameLen = getStrLen(name);

	cout << "Enter ID: ";
	cin >> id;

	if (!citizensDB.isCitizenExistsById(id)) {

		cout << "Enter year of birth: ";
		cin >> year;

		cout << "Enter district number: ";
		cin >> districtNum;

		if (districtsArr.isDistExist(districtNum)) {
			Citizen newCitizen(name, nameLen, id, year, &districtsArr[districtNum]);
			citizensDB[districtNum].add(newCitizen);
		}
		else 
			cout << "The district with id " << districtNum << " does not exists!!!" << endl;
	}
	else
		cout << "The citizen with id " << id << " already exists!!" << endl;
}
// ( 3 )
void addNewParty(PartiesArr& partiesArr, DistrictsArr& districtsArr, CitizensDB& citizensDB)
{
	char name[20]; int nameLen; long int id;

	cout << "Enter party's name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	nameLen = getStrLen(name);

	cout << "Enter ID of the party leader: ";
	cin >> id;

	if (citizensDB.isCitizenExistsById(id)) {
		if (!partiesArr.isCitizenAlreadyLeader(id)) {
			Party newParty(name, nameLen, id, districtsArr.getLogSize());

			districtsArr.addNewPartyToVotesCounters(); // adding counter to new party in each district
			partiesArr.add(newParty);

		}
		else
			cout << "The citizen with the id " << id << " is already a party leader!!" << endl;
	}
	else
		cout << "No citizen with id " << id << " found!!!" << endl;

}
// ( 4 )
void addNewRep(PartiesArr& partiesArr, CitizensDB& citizensDB, DistrictsArr& districtsArr)
{
	int partyNum, districtNum; long int repId;

	cout << "Enter ID of rep: ";
	cin >> repId;

	if (citizensDB.isCitizenExistsById(repId)) {
		Citizen rep = citizensDB[repId];
		if (!partiesArr.isCitizenAlreadyRep(repId)) {
			cout << "Enter party number: ";
			cin >> partyNum;

			if ((partyNum < partiesArr.getLogSize()) && (partyNum >= 0)) {
				cout << "Enter district number: ";
				cin >> districtNum;

				if ((districtNum < districtsArr.getLogSize()) && (districtNum >= 0))
					partiesArr.addRep(rep, partyNum, districtNum);
				else
					cout << "The district with the number " << districtNum << " does not exists!!" << endl;
			}
			else
				cout << "The party with the number " << partyNum << " does not exists!!" << endl;
		}
		else
			cout << "The citizen with id " << repId << " is already representative!!" << endl;
	}
	else
		cout << "The citizen with id " << repId << " does not exists!" << endl;
}
// ( 8 )
void addNewVote(CitizensArr& citizensArr, PartiesArr& partiesArr)
{
	long int ID;
	int partyID;
	int districtNum;
	Citizen* voter;

	/*cout << "Enter your ID: ";
	cin >> ID;

	voter = citizensArr.getCitizenById(ID);

	if (voter != nullptr) {
		if (!(voter->getVoted())) {
			voter->setVoted(true);

			cout << "Enter party: ";
			cin >> partyID;

			districtNum = voter->getDistrictNum();

			partiesArr.addVoteToDistrictInParty(partyID, districtNum);

		}

		else
			cout << "Voter with id " << ID << " has already voted!!" << endl;
	}

	else
		cout << "Voter with id " << ID << " not found!!" << endl;*/
}

int getStrLen(char* name) {
	int i = 0;

	while (name[i] != '\0')
		i++;

	return i;
}

void printMenu()
{
	cout << "Enter Action: " << endl;
	cout << "1 - add district" << endl;
	cout << "2 - add citizen" << endl;
	cout << "3 - add party" << endl;
	cout << "4 - add representative" << endl;
	cout << "5 - Show all districts" << endl;
	cout << "6 - show all citizens" << endl;
	cout << "7 - show all parties" << endl;
	cout << "8 - vote" << endl;
	cout << "9 - show election polls" << endl;
	cout << "10 - Exit" << endl;


}

