#include <iostream>
#include "District.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;

namespace elections {
	District::District() : name(nullptr), nameLen(0), numOfRep(0), districtNum(0), citizensNum(0) {}

	District::District(char* _name, int _nameLen, int _numOfRep, int _districtNum) {
		nameLen = _nameLen;
		numOfRep = _numOfRep;
		districtNum = _districtNum;
		name = new char[_nameLen + 1];
		citizensNum = 0;
		memcpy(name, _name, nameLen + 1);

		name[nameLen] = '\0';
	}

	District::District(const District& other)
	{
		*this = other;
	}

	District::~District()
	{
		delete[] name;
	}


	void District::operator=(const District& other)
	{
		numOfRep = other.numOfRep;
		nameLen = other.nameLen;
		districtNum = other.districtNum;
		votesCounter = other.votesCounter;
		name = new char[nameLen + 1];
		citizensNum = other.citizensNum;

		for (int i = 0; i < other.nameLen; i++)
			name[i] = other.name[i];

		name[nameLen] = '\0';
	}
	const int District::getDistrictNum(void) const
	{
		return districtNum;
	}

	const char* District::getDistrictName() const
	{
		return name;
	}
	const int District::getNumOfRep() const
	{
		return numOfRep;
	}
	const int District::getCitizensNum() const
	{
		return citizensNum;
	}
	const VotesCounter& District::getVotesCounter()
	{
		return votesCounter;
	}
	void District::addVotesCountersForNewParty()
	{
		votesCounter.addEmptyCounter();
	}
	void District::addVoteToVotesCountersInIdx(int partyNum)
	{
		votesCounter.addVote(partyNum);
		votesCounter.updatePercentage();
	}
	const int District::getVotesInIndex(int idx) const
	{
		return votesCounter[idx];
	}

	void District::addOneCitizen()
	{
		citizensNum++;
	}

	void District::save(ostream& out) const
	{
		out.write(name, nameLen);
		out.write(rcastcc(&nameLen), sizeof(nameLen));
		out.write(rcastcc(&numOfRep), sizeof(numOfRep));
		out.write(rcastcc(&districtNum), sizeof(districtNum));
		votesCounter.save(out);
	}

	void District::load(istream& in)
	{
		in.read(name, nameLen);
		in.read(rcastc(&nameLen), sizeof(nameLen));
		in.read(rcastc(&numOfRep), sizeof(numOfRep));
		in.read(rcastc(&districtNum), sizeof(districtNum));
		votesCounter.load(in);
	}

	ostream& operator<<(ostream& os, District& district)
	{
		cout << "District Number: " << district.getDistrictNum()
			<< " | Name: " << district.getDistrictName() << " | Number of representative: "
			<< district.getNumOfRep() <<" | Number of citizens: " << district.getCitizensNum() <<  endl;


		// TEST - change district to const

		int votingNumber = district.votesCounter.getVotingNumberInDistrict();
		
		VotesCounter  votesCounter = district.getVotesCounter();
		int* votesByParty = votesCounter.getVotesByParty();
		int* votesPerc = votesCounter.getPercentageVotes();
		cout << "votes: ";
		for (int i = 0; i < votesCounter.getLogSize(); i++)
		{
			cout << votesByParty[i] << " ";
		}
		cout << endl;
		cout << "perc: ";
		for (int i = 0; i < votesCounter.getLogSize(); i++)
		{
			cout << votesPerc[i] << " ";
		}
		cout << endl;


		return os;
	}
}

