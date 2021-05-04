#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace
{

	void helloWorld() {

		int term = 0;

		switch (term) {

		case 0: {
			std::cout << "\n\tHello world.\n";
			break;
		};
		case 1: {
			using namespace std;
			cout << "\n\tHello, programming.\n\tHere we go!\n";
			break;
		};
		}
	}

	struct location {
		double x, y;
		bool equals(location l) { return x == l.x && y == l.y; }
	};

	void exc02_goToBathroom() {

		//the initial state before going to bathroom
		bool peepee = false, poopoo = false, standing = false;

		location currentPosistion;
		location destination;

		//basic necessary information to move to bathrom
		location bathroom = location();

		//basic implementation of preparing to move to the bathroom
		auto standUp = [&] {if (!standing) standing = true; };

		// basic implementation of the process of moving to the bathroom
		auto relocate = [&] {currentPosistion = destination;  };

		if (peepee || poopoo) {

			standUp();
			if (!(destination.equals(bathroom))) destination = bathroom;
			relocate();
		}
	}

	void exc03_goTo(location currentPosition, location destination) {
	//https://www.youtube.com/watch?v=NbSee-XM7WA
	}

	void exc04_cookbook() {

		/* Pyzy.
		template<typename utensils> makePyzy(){
	
			ingredient potatoes = (get(rawPotatoes, kg 2)).peel();	
			ingredient dividedPotatoes[2] = potatoes.divide(1./3.);
			utensils pot1 = pot().add(water.add(salt));
			utensils bowl1;
	
			dividedPotatoes[1] = grind( strain( cook( potatoes[1], pot1)));
			dividedPotatoes[2] = ( potatoes[2].grate()).squezeOutTo(water, bowl1);

			bowl1.precipitate(residue, water);
			~bowl1.water();

			utensils bowl2;

			for(ingredient i: dividedPotatoes) bowl2.add(i);

			bowl2.add( 2 * spoonfull(potatoFlour));
			bowl2.add( bowl1.remove(residue));
			bowl2.add( pinch(salt));
			bowl2.blend();

			utensils pot2 = pot(BIG_ONE).add(water);
			pot2.boil();
			pot2.add(spoonfull(salt));

			utensils bowl3;

			while(!empty(bowl2)){

				vector<pyza> pyzy;
				int count = rand() % 3 + 5;
		
				for(int i = 0; i < count; ++i) pyzy.push_back(pyza(bowl2));
				for(pyza p : pyzy) pot2.add(pyza);

				wait_until(pyzy.locate() == surface) + wait(minutes 3);
				bowl3.add(scoop(pot2, pyzy));
			}
			return bowl3;
		}
	
		*/


	}

}