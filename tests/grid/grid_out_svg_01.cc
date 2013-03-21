#include "../tests.h"

#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/tria_boundary_lib.h>
#include <deal.II/grid/grid_out.h>

#include <fstream>
#include <cmath>

using namespace dealii;

Triangulation<2,2> create_grid()
{
	Triangulation<2,2> triangulation;

	double inner_radius = .5;
	double outer_radius = 1.;

	Point<2> center(0., 0.);

	GridGenerator::hyper_cube_with_cylindrical_hole(triangulation, inner_radius, outer_radius);
	triangulation.refine_global(1);

	Triangulation<2>::active_cell_iterator

	cell = triangulation.begin_active(),
	endc = triangulation.end();

	for(; cell!=endc; ++cell)
	{
		for (unsigned int v=0; v < GeometryInfo<2>::vertices_per_cell; ++v)
		{
			const double distance_from_center = center.distance(cell->vertex(v));

			if (std::fabs(distance_from_center - inner_radius) < .25)
			{
				cell->set_refine_flag();
				break;
			}
		}
	}

	triangulation.execute_coarsening_and_refinement();

	return triangulation;
}

int main()
{
	initlog(__FILE__);

	GridOut grid_out;
	GridOutFlags::Svg svg_flags;

	svg_flags.coloring = GridOutFlags::Svg::level_number;
	svg_flags.label_material_id = true;

	grid_out.set_flags(svg_flags);
	grid_out.write_svg(create_grid(), deallog.get_file_stream());

	return 0;
}