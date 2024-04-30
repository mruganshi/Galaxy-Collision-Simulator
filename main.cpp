#include <SFML/Graphics.hpp>
#include "galaxy.h"
#include "tree.h"
using namespace sf;

void collider(int N){
	std::vector<Galaxy> g;

	for(int i=0;i<N;i++){
		Galaxy galaxy = Galaxy(i,300,rand()%1600-800,rand()%1600-800,300);
		g.push_back(galaxy);
	}

	RenderWindow window(VideoMode(2048, 2048),"Galaxy Simulator");

	std::vector <CircleShape> s;
	std::vector <CircleShape> bh;
	for(int i=0;i<N;i++){
		int n = g[i].number_of_stars;
		CircleShape black_hole(10);
		black_hole.setPosition(1024+g[i].black_hole_centre.position.x,1024-g[i].black_hole_centre.position.y);
		black_hole.setOutlineColor(Color(255, 215, 0, 100));
		black_hole.setFillColor(Color(0,0,0,100));
		Color random_color = Color(rand()%256,rand()%256,rand()%256,255);
		bh.push_back(black_hole);
		for(int j=0;j<n;j++){
			CircleShape star(2);
			star.setPosition(1024+g[i].stars[j].position.x,1024-g[i].stars[j].position.y);
			star.setFillColor(random_color);
			s.push_back(star);
		}
	}
	

	while (window.isOpen())
	{
		Event event;
		while (
			window.pollEvent(event))
			if (event.type ==
				Event::Closed)
				window.close();

		window.clear();
		Tree bh_tree;
		for(int i=0;i<N;i++){
			bh_tree.insert(&(g[i].black_hole_centre));
			int n = g[i].number_of_stars;
			for(int j=0;j<n;j++){
				bh_tree.insert(g[i].stars+j);
			}			
		}
		bh_tree.calc_force_and_move();

		for(int i=0;i<N;i++){
			int n = g[i].number_of_stars;
			bh[i].setPosition(1024+g[i].black_hole_centre.position.x,1024-g[i].black_hole_centre.position.y);
			window.draw(bh[i]);
			for(int j=0;j<n;j++){
				s[n*i+j].setPosition(1024+g[i].stars[j].position.x,1024-g[i].stars[j].position.y);
				window.draw(s[n*i+j]);
			}
		}
		window.display();
	}

}

int main()
{
	srand(time(0));
	std::cout<<"Enter the number of galaxies: ";
	int N;
	std::cin>>N;
	collider(N);
	return 0;
}
