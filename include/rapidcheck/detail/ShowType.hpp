#pragma once

namespace rc {
namespace detail {

template<typename T> struct ShowType
{
    static void showType(std::ostream &os)
    {
        os << demangle(typeid(T).name());
    }
};

template<typename T, typename Allocator>
struct ShowType<std::vector<T, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::vector<";
        detail::showType<T>(os);
        os << ">";
    }
};

template<typename T, typename Allocator>
struct ShowType<std::deque<T, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::deque<";
        detail::showType<T>(os);
        os << ">";
    }
};

template<typename T, typename Allocator>
struct ShowType<std::forward_list<T, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::forward_list<";
        detail::showType<T>(os);
        os << ">";
    }
};

template<typename T, typename Allocator>
struct ShowType<std::list<T, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::list<";
        detail::showType<T>(os);
        os << ">";
    }
};

template<typename Key, typename Compare, typename Allocator>
struct ShowType<std::set<Key, Compare, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::set<";
        detail::showType<Key>(os);
        os << ">";
    }
};

template<typename Key,
         typename T,
         typename Compare,
         typename Allocator>
struct ShowType<std::map<Key, T, Compare, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::map<";
        detail::showType<Key>(os);
        os << ", ";
        detail::showType<T>(os);
        os << ">";
    }
};

template<typename Key, typename Compare, typename Allocator>
struct ShowType<std::multiset<Key, Compare, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::multiset<";
        detail::showType<Key>(os);
        os << ">";
    }
};

template<typename Key,
         typename T,
         typename Compare,
         typename Allocator>
struct ShowType<std::multimap<Key, T, Compare, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::multimap<";
        detail::showType<Key>(os);
        os << ", ";
        detail::showType<T>(os);
        os << ">";
    }
};

template<typename Key,
         typename Hash,
         typename KeyEqual,
         typename Allocator>
struct ShowType<std::unordered_set<Key, Hash, KeyEqual, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::unordered_set<";
        detail::showType<Key>(os);
        os << ">";
    }
};

template<typename Key,
         typename T,
         typename Hash,
         typename KeyEqual,
         typename Allocator>
struct ShowType<std::unordered_map<Key, T, Hash, KeyEqual, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::unordered_map<";
        detail::showType<Key>(os);
        os << ", ";
        detail::showType<T>(os);
        os << ">";
    }
};

template<typename Key,
         typename T,
         typename Hash,
         typename KeyEqual,
         typename Allocator>
struct ShowType<std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::unordered_multimap<";
        detail::showType<Key>(os);
        os << ", ";
        detail::showType<T>(os);
        os << ">";
    }
};

template<typename Key,
         typename Hash,
         typename KeyEqual,
         typename Allocator>
struct ShowType<std::unordered_multiset<Key, Hash, KeyEqual, Allocator>>
{
    static void showType(std::ostream &os)
    {
        os << "std::unordered_multiset<";
        detail::showType<Key>(os);
        os << ">";
    }
};

template<typename T, std::size_t N>
struct ShowType<std::array<T, N>>
{
    static void showType(std::ostream &os)
    {
        os << "std::array<";
        detail::showType<T>(os);
        os << ", " << N << ">";
    }
};

template<typename T>
void showType(std::ostream &os)
{
    ShowType<T>::showType(os);
}

template<typename T>
std::string typeToString()
{
    std::ostringstream ss;
    showType<T>(ss);
    return ss.str();
}

} // namespace detail
} // namespace rc