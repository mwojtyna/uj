import java.util.Set;

class RectangularIntegration implements NumericalIntegration {
    private Function f;

    public static void main(String[] args) {
        // f(x) = x
        {
            RectangularIntegration integration = new RectangularIntegration();
            Function f = new Function() {
                @Override
                public Set<Range> domainExclusions() {
                    return Set.of(new Range() {
                        @Override
                        public double min() {
                            return 5;
                        }

                        @Override
                        public double max() {
                            return 8;
                        }
                    }, new Range() {
                        @Override
                        public double min() {
                            return 0;
                        }

                        @Override
                        public double max() {
                            return 1;
                        }
                    });
                }

                @Override
                public double apply(double x) {
                    return 1 / x;
                }
            };
            Range range = new Range() {
                @Override
                public double min() {
                    return 0;
                }

                @Override
                public double max() {
                    return 10;
                }
            };
            integration.setFunction(f);
            double area = integration.integrate(range, 1_000);
            System.out.println(area);
        }
    }

    @Override
    public void setFunction(Function f) {
        this.f = f;
    }

    @Override
    public double integrate(Range range, int subintervals) {
        double area = 0;
        double dx = (range.max() - range.min()) / subintervals;

        for (int i = 0; i < subintervals; i++) {
            double x = range.min() + (i + 0.5) * dx;
            if (excluded(x)) {
                continue;
            }

            double dy = f.apply(x);
            area += dx * dy;
        }

        return area;
    }

    private boolean excluded(double x) {
        for (Range range : this.f.domainExclusions()) {
            if (range.min() <= x && x <= range.max()) {
                return true;
            }
        }
        return false;
    }
}
