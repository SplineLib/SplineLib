import os, sys
sys.path.append(os.getcwd())

import splinelyp


b_spline = splinelyp.BSpline1d1d([[0.0, 0.0, 0.5, 1.0, 1.0]], [1], [[0.0], [0.75], [1.0]])

knot = b_spline.knot_vectors[0][2]
if knot != 0.5:
    sys.exit("Accessing knot vectors failed: knot is {} instead of 0.5!".format(knot))
degree = b_spline.degrees[0]
if degree != 1:
    sys.exit("Accessing degrees failed: degree is {} instead of 1!".format(degree))
scalar_coordinate = b_spline.coordinates[2][0]
if scalar_coordinate != 1.0:
    sys.exit("Accessing coordinates failed: scalar coordinate is {} instead of 1.0!".format(scalar_coordinate))

evaluation = b_spline.evaluate([[0.25]])[0]
if evaluation != [0.375]:
    sys.exit("Evaluate failed: result is {} instead of 0.375!".format(evaluation[0]))
derivative = b_spline.derivative([[0.25]], [1])[0]
if derivative != [1.5]:
    sys.exit("Derivative failed: result is {} instead of 1.5!".format(derivative[0]))

b_spline.insert_knots(0, [0.25])
knot = b_spline.knot_vectors[0][2]
if knot != 0.25:
    sys.exit("Knot insertions failed: knot is {} instead of 0.25!".format(knot))
multiplicity = b_spline.remove_knots(0, [0.25], 1e-8)
knot = b_spline.knot_vectors[0][2]
if (multiplicity != 1) or (knot != 0.5):
    sys.exit("Knot removals failed: knot is {} instead of 0.5!".format(knot))
b_spline.elevate_degree(0)
degree = b_spline.degrees[0]
if degree != 2:
    sys.exit("Degree elevation failed: degree is {} instead of 2!".format(knot))
was_reduced = b_spline.reduce_degree(0, 1e-8)
degree = b_spline.degrees[0]
if (not was_reduced) or (degree != 1):
    sys.exit("Degree reduction failed: degree is {} instead of 1!".format(knot))


coordinate = b_spline.sample([4])[1]
if coordinate != [0.5]:
    sys.exit("Sampling failed: scalar coordinate is {} instead of 0.5!".format(coordinate[0]))
knots = b_spline.write()[0][0][0]
if knots != ["0", "0", "0.5", "1", "1"]:
    sys.exit("Write failed: knot is " + knots[0] + " instead of 0!")

representation = repr(b_spline)
if representation != "<splinelyp.BSpline1d1d>":
    sys.exit("Representation is \"" + representation + "\" instead of \"" + "<splinelyp.BSpline1d1d>" + "\"!")


nurbs = splinelyp.Nurbs1d1d([[0.0, 0.0, 0.5, 1.0, 1.0]], [1], [[0.0], [0.75], [1.0]], [2.0, 2.0, 2.0])

scalar_coordinate = nurbs.homogeneous_coordinates[1][0]
if scalar_coordinate != 1.5:
    sys.exit("Accessing homogeneous coordinates failed: scalar homogeneous coordinate is {} instead of "
             "1.5!".format(scalar_coordinate))
weight = nurbs.homogeneous_coordinates[1][1]
if weight != 2.0:
    sys.exit("Accessing homogeneous coordinates failed: weight is {} instead of 2.0!".format(weight))

weights = nurbs.write()[1][1]
if weights != ["2", "2", "2"]:
    sys.exit("Write failed: weight is " + weights[0] + " instead of 2!")

representation = repr(nurbs)
if representation != "<splinelyp.Nurbs1d1d>":
    sys.exit("Representation is \"" + representation + "\" instead of \"" + "<splinelyp.Nurbs1d1d>" + "\"!")
