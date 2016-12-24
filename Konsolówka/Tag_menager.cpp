#include "Tag_menager.h"


//Albo jestem têpy, albo ktoœ bardzo na o nie wpad³ robi¹c c++ -_-
string Int_TO_String(int a)
{
	stringstream converter;
	converter << a;
	string returner;
	converter >> returner;
	return returner;
}

Tag_and_its_name* Tag_menager::find_const_by_value(string value)
{

	for (int i = 0; i < Const_tags_vector.size(); i ++)
	{
		if (Tags_vector[Const_tags_vector[i]].name == value)
		{
			return &Tags_vector[Const_tags_vector[i]];
		}
	}

	return nullptr;
}

bool Tag_menager::add_const(string value)
{
	string new_tag{ "t" + Int_TO_String(Tags_vector.size()) };
	if (this->find_const_by_value(value) == nullptr)
	{
		Tags_vector.push_back(Tag_and_its_name(value, new_tag, constant));
		Const_tags_vector.push_back(Tags_vector.size() - 1);
		return true;
	}
	return false;
}


Tag_and_its_name* Tag_menager::find_by_tag(string tag_to_find)
{
	for (unsigned int i = 0; i < Tags_vector.size(); i++)
	{
		if (Tags_vector[i].tag == tag_to_find)
		{
			return &(Tags_vector[i]);
		}
	}
	return nullptr;
}

Tag_and_its_name* Tag_menager::find_by_name(string name_to_find)
{
	for (int i = 0; i < Tags_vector.size(); i++)
	{
		if (Tags_vector[i].name == name_to_find)
		{
			return &(Tags_vector[i]);
		}
	}
	return nullptr;
}

void Tag_menager::add(Tag_and_its_name adder)
{
	Tags_vector.push_back(adder);
}

int Tag_menager::how_many_tags()
{
	return Tags_vector.size();
}

void Tag_menager::add(string name, int type)
{
	string new_tag{"t" + Int_TO_String( Tags_vector.size() )};
	if (this->find_by_name(name) == nullptr)
	{
		Tags_vector.push_back(Tag_and_its_name(name, new_tag, type));
	}
	else
	{
		throw string("\tB³¹d: \n\t\tpróbca redefinicji nazwy: " + name);
	}
}

const string Tag_menager::get_last_tag()
{
	return Tags_vector.back().tag;
}

const string Tag_menager::get_last_constant_tag()
{
	return Tags_vector[Const_tags_vector.back()].tag;
}

const string Tag_menager::get_tag_by_name(string name)
{
	Tag_and_its_name *ptr_to_object = this->find_by_name(name);

	if (ptr_to_object != nullptr)
	{
		return ptr_to_object->tag;
	}
	throw string("\tB³¹d: \n\t\tOdwo³anie do nizdefiniowanej nazwy: " + name);
	
}

const string Tag_menager::get_tag_by_const_value(string value)
{
	return (this->find_const_by_value(value))->tag;
}

const string Tag_menager::add_next_jump_tag()
{
	this->add("0JUMP" + Int_TO_String(number_of_jump_meta_tags), meta_tag);
	number_of_jump_meta_tags++;
	return this->get_last_jump_name();
}

const string Tag_menager::get_last_jump_tag()
{
	return (this->find_by_name("0JUMP" + Int_TO_String(number_of_jump_meta_tags - 1)))->tag;
}

const string Tag_menager::get_last_jump_name()
{
	return "0JUMP" + Int_TO_String(number_of_jump_meta_tags - 1);
}

const string Tag_menager::get_LAST_BUT_ONE_jump_tag()
{
	return (this->find_by_name("0JUMP" + Int_TO_String(number_of_jump_meta_tags - 2)))->tag;
}


Tag_menager::Tag_menager()
{
}


Tag_menager::~Tag_menager()
{
}




//--------------------------------------------------------------
