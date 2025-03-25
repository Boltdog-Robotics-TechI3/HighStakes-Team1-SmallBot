class Distance {
    private:
        double distIN;
        Distance(double inches);
    public:
        static Distance fromIN(double inches);
        static Distance fromFT(double ft);
        static Distance fromYD(double yd);

        double asIN();
        double asFT();
        double asYD();
};

inline Distance operator ""_ins(long double ins) {
    return Distance::fromIN(ins);
}

inline Distance operator ""_fts(long double feet) {
    return Distance::fromFT(feet);
}

inline Distance operator ""_yds(long double yards) {
    return Distance::fromYD(yards);
}

inline Distance operator ""_ins(unsigned long long ins) {
    return Distance::fromIN(ins);
}

inline Distance operator ""_fts(unsigned long long feet) {
    return Distance::fromFT(feet);
}

inline Distance operator ""_yds(unsigned long long yards) {
    return Distance::fromYD(yards);
}