#pragma once
#include "Party.h"
#include "CitizensArr.h"

namespace elections {
	class PartiesArr {
	private:
		int logSize = 0, phsSize = 0;
		Party* parties;

		// Resizing parties arr and updating logSize, phsSize
		void resize(int size);

	public:
		// Ctor
		PartiesArr();
		// copy ctor
		PartiesArr(const PartiesArr&);
		// Dtor
		~PartiesArr();

		// Overload "=" operator
		void operator=(const PartiesArr&);

		// Setters---------------------------------------------------------
		// add one party to partiesArr
		void add(Party& party);

		// add rep to party in index partyNum to it's array in index districtNum
		void addRep(Citizen& rep, int partyNum, int districtNum);

		// allocating one more space to each party when district is added
		void addNewDistToRepArr(void);

		// Getters----------------------------------------------------------------
		const int getLogSize() const;

		Party& operator[](int index) const;

		// returns true if citizen with the id is already leader
		const bool isCitizenAlreadyLeader(long int id) const;

		// returns true if citizen with the id is already rep
		const bool isCitizenAlreadyRep(long int id) const;

		friend ostream& operator<<(ostream& os, const PartiesArr& partiesArr);

	};
}