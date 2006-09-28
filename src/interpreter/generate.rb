#!/usr/bin/ruby

#  Copyright (C) 2005-2006 by Cies Breijs
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of version 2 of the GNU General Public
#  License as published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public
#  License along with this program; if not, write to the Free
#  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
#  Boston, MA 02110-1301, USA.


require 'cgi'


@type_dict = {
	:bool   => ["Bool",   "bool()",   "bool"],
	:number => ["Number", "number()", "double"],
	:string => ["String", "string()", "QString"]
}

@cat_hash = {}
@total_generated_lines = 0

def make_headers()
	puts "making headers"

	c_warning =
<<EOS
/* The code between the line that start with "//BEGIN GENERATED" and "//END GENERATED"
 * is generated by "generate.rb" according to the definitions specified in
 * "definitions.rb". Please make all changes in the "definitions.rb" file, since all
 * all change you make here will be overwritten the next time "generate.rb" is run.
 * Thanks for looking at the code!
 */\n
EOS

	dict_header =
<<EOS
<?xml version="1.0"?>
<!DOCTYPE KTurtleDictionary>\n
<KTurtleDictionary lang="en_US" ver="0.01">\n
<!--  If this file is named "KTurtleDictionary.en_US.xml" it is quite likely generated
      by "generate.rb" according to the definitions specified in "definitions.rb".
      Please make all changes in the "definitions.rb" file, since all all change you
      make here will be overwritten the next time "generate.rb" is run.
      Thanks for looking at the code!
-->\n
EOS


	# fills the 'enum Token::Type' in token.h
	@token_type_h           = c_warning

	# fills the 'enum Token::Category' in token.h
	@token_category_h       = c_warning

	# fills the switch statement in the typeToCategory() method
	@token_switch_cpp       = c_warning

	# fills the dictionary
	@dictionary_xml         = dict_header

	# fills the 'stringType2intType()'
	@translator_cpp         = c_warning

	# for in the statement switch
	@parser_statements_cpp  = c_warning

	# declaration of the parse* methods
	@parser_h               = c_warning

	# definition of the parse* methods
	@parser_cpp             = c_warning

	# declaration of the execute* methods
	@executer_h             = c_warning

	# fills the signal declaration block in the executer.h
	@executer_emits_h       = c_warning

	# definition of the execute* methods
	@executer_cpp           = c_warning

	# fills the switch statement in the execute(TreeNode* node) method
	@executer_switch_cpp    = c_warning

	# fills the connectAllSlots method of the dummy signal receiver
	@echoer_connect_h       = c_warning

	# definition of the slots in the dummy signal receiver
	@echoer_slots_h         = c_warning

	# simple includes file that contains the connect statements for the mainwindow
	@gui_connect_inc        = c_warning

	# will become the help file generation
	@help_docbook           = ''
end



def make_footers()
	puts "making footers\n\n"

	@dictionary_xml += "\n\n</KTurtleDictionary>"
	# helpfile footer here
end



def new_item()
# reset the variables

# @type,    the internal name of the item
# @look,    the en_US look for the item
# @ali,     the alias (another en_US look)
# @p_def,   method definition for the parser
# @e_def,   method definition for the executer
# @funct,   the functionality the item should be given
# @cat,     the category the item belongs to
# @help,    .docbook formatted text for in a help file

	@type  = ''
	@look  = ''
	@localize = true
	@ali   = ''
	@p_def = ''
	@e_def = ''
	@emit  = ''
	@funct = ''
	@cat   = nil
	@args  = []
	@help  = ''
end


def same_args(args)
	result = true
	for item in @args do
		result = (item == @args[0])
	end
	return result
end


def parse_item()
	puts "parsing item '#{@type}'"

	@token_type_h += "\t\t\t#{@type},\n"

	@cat_hash[@type] = @cat if @cat

	if !@look.empty?
		@dictionary_xml += "\t<token type=\"#{@type}\">\n\t\t<look>#{CGI.escapeHTML(@look)}</look>\n"
		if !@ali.empty?
			@dictionary_xml += "\t\t<look>#{CGI.escapeHTML(@ali)}</look>\n"
		end
		@dictionary_xml += "\t</token>\n\n"
	end

# 	@translator_cpp += "\tif (typeString == \"#{@type}\")".ljust(40) + " return Token::#{@type};\n"

	unless @look.empty?
		if @localize
			@translator_cpp +=
<<EOS
	localizedCommandLook = ki18nc(
		"You are about to translate the '#{@type}' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translators.php to learn know how to properly translate it.",
		"#{@look}").toString(localizer);
	default2localizedMap["#{@look}"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::#{@type};

EOS
		else
			escaped_look = (@look == '"') ? '\"' : @look
			@translator_cpp += "\tlook2typeMap[\"#{escaped_look}\"] = Token::#{@type};\n\n"
		end
	end

	if @funct =~ /statement/

		if @p_def.empty?
			if @args[0] == :none
				@p_def =
<<EOS
	TreeNode* node = new TreeNode(currentToken);
	nextToken();
	matchToken(Token::EndOfLine, *node->token());
	return node;
EOS
			end
		
			if @args[0] != :none and !@args.empty?
				@p_def =
<<EOS
	TreeNode* node = new TreeNode(currentToken);
	nextToken();
	appendArguments(node);
	matchToken(Token::EndOfLine, *node->token());
	return node;
EOS
			end
		end

		if @p_def.empty? # if still empty...
			@p_def = "\treturn 0;  // this is a stud\n"
		end

		@parser_statements_cpp += "\t\tcase Token::#{@type}".ljust(33) + " : return parse#{@type}();\n"
	end

	if !@p_def.empty?
		@parser_h += "\t\tTreeNode* parse#{@type}();\n"
		@p_def =
<<EOS
TreeNode* Parser::parse#{@type}() {
	qDebug() << "Parser::parse#{@type}()";
#{@p_def}}
EOS
		@parser_cpp += @p_def
	end

	if @funct =~ /node/
		if @funct =~ /constant/
			@executer_switch_cpp += "\t\tcase Token::#{@type}".ljust(33) + " : /* a constant; do nothing */".ljust(37) + "break;\n"
		else
			@executer_switch_cpp += "\t\tcase Token::#{@type}".ljust(33) + " : execute#{@type}(node);".ljust(37) + "break;\n"
			@executer_h += "\t\tvoid execute#{@type}(TreeNode* node);\n"
		end

		if @e_def.empty? and @args.length() > 0
				if @args[0] == :none
					@e_def += "\tif (!checkParameterQuantity(node, 0, 20000+Token::#{@type}*100+90)) return;\n"
				elsif same_args(@args)
						@e_def += "\tif (!checkParameterQuantity(node, #{@args.length()}, 20000+Token::#{@type}*100+90) ||\n\t\t!checkParameterType(node, Value::#{@type_dict[@args[0]][0]}, 20000+Token::#{@type}*100+91)) return;\n"
				end
		end

		if @funct =~ /auto-emit/ and @args.length() > 0 and @emit.empty?
			# this build the emit statement for executer.cpp and the signal declaration for the executer.h

			# find the method name:
			method_name_str = @type[0].chr.downcase + @type[1..-1]

			# now parse the arguments (if any) into a arguments_str and a e_def_addition:
			arguments_str = ''
			e_def_emit_call_args = ''
			named_arguments_str = ''
			output_arguments_code = ''
			if @args[0] != :none
				i = 0
				for arg in @args
					e_def_emit_call_args += "node->child(#{i})->value()->#{@type_dict[arg][1]}, "
					arguments_str += @type_dict[arg][2] + ", "
					named_arguments_str += "#{@type_dict[arg][2]} arg#{i}, "
					output_arguments_code += "arg#{i} << \",\" << "
					i = i + 1
				end
				e_def_emit_call_args = e_def_emit_call_args[0..-3]  # strip the extra ', '
				arguments_str = arguments_str[0..-3]
				named_arguments_str = named_arguments_str[0..-3]
				output_arguments_code = output_arguments_code[0..-8]
			end

			@e_def += "\temit #{method_name_str}(#{e_def_emit_call_args});\n"
			@executer_emits_h += "\t\tvoid #{method_name_str}(#{arguments_str});\n"
			@echoer_connect_h += "\t\t\tconnect(executer, SIGNAL(#{method_name_str}(#{arguments_str})), \n\t\t\t\tSLOT(#{method_name_str}(#{arguments_str})));\n"
			@echoer_slots_h   += "\t\tvoid #{method_name_str}(#{named_arguments_str}) { *output << \"#{method_name_str}\" << \"(\" << #{output_arguments_code}\")\\n\"; }\n"
			@gui_connect_inc  += "\tconnect(executer, SIGNAL(#{method_name_str}(#{arguments_str})), \n\t\tcanvas, SLOT(slot#{method_name_str[0..0].upcase+method_name_str[1..-1]}(#{arguments_str})));\n"
		end

		if @e_def.empty?
			@e_def = "\tnode = node; // stop the warnings // this is a stud\n"
		end

		unless @funct =~ /constant/
			@executer_cpp +=
<<EOS
void Executer::execute#{@type}(TreeNode* node) {
	qDebug() << "Executer::execute#{@type}()";
#{@e_def}}
EOS
		end
	end

end



def write_files(diff)
	if diff
		puts "diff'ing files (not writing):\n\n"
	else
		puts "writing files:\n\n"
	end

	@cat_hash.values.uniq.each do |v1|
		@token_category_h += "\t\t\t#{v1}Category,\n"
		@cat_hash.each_pair do |k,v2|
			if v2 == v1
				@token_switch_cpp += "\t\tcase #{k}:\n"
			end
		end
		@token_switch_cpp += "\t\t\treturn #{v1}Category;\n\n"
	end

	parse_and_write("./token.h", @token_type_h[0..-3]+"\n", "token_type_h", diff);
	parse_and_write("./token.h", @token_category_h[0..-3]+"\n", "token_category_h", diff);
	parse_and_write("./token.cpp", @token_switch_cpp, "token_switch_cpp", diff);
	@dictionary_xml.each_line { @total_generated_lines += 1 }
	          write("./KTurtleDictionary.en_US.xml", @dictionary_xml, diff);
	parse_and_write("./translator.cpp", @translator_cpp, "translator_cpp", diff);
	parse_and_write("./parser.h", @parser_h, "parser_h", diff);
	parse_and_write("./parser.cpp", @parser_cpp, "parser_cpp", diff);
	parse_and_write("./parser.cpp", @parser_statements_cpp, "parser_statements_cpp", diff);
	parse_and_write("./executer.h", @executer_h, "executer_h", diff);
	parse_and_write("./executer.h", @executer_emits_h, "executer_emits_h", diff);
	parse_and_write("./executer.cpp", @executer_cpp, "executer_cpp", diff);
	parse_and_write("./executer.cpp", @executer_switch_cpp, "executer_switch_cpp", diff);
	parse_and_write("./echoer.h", @echoer_connect_h, "echoer_connect_h", diff);
	parse_and_write("./echoer.h", @echoer_slots_h, "echoer_slots_h", diff);
	parse_and_write("./gui_connect.inc", @gui_connect_inc, "gui_connect_inc", diff);
	#          write("./?.docbook", @help_docbook);
	#          write("./?.xml", @highlighttheme);
end



def parse_and_write(file_name, string, identifier, diff)
	string.each_line { @total_generated_lines += 1 }

	puts "parsing '#{file_name}'"

	file = File.new(file_name)

	rx_begin = Regexp.new("^//BEGIN GENERATED " + identifier + " CODE")
	rx_end   = Regexp.new("^//END GENERATED "   + identifier + " CODE")
	parsed = ""
	g = false  # true if we're in the parse scope
	i = 0      # line count
	file.each_line { |line|
		i += 1

		if line =~ rx_end
			puts "found '//END GENERATED #{identifier} CODE' in '" + file_name + "' on line " + i.to_s
			parsed += "\n" + string + "\n"
			g = false
		end

		if !g
			parsed += line
		end

		if line =~ rx_begin
			puts "found '//BEGIN GENERATED #{identifier} CODE' in '" + file_name + "' on line " + i.to_s
			g = true
		end
	}
	file.close()
	write(file_name, parsed, diff)
end



def write(file_name, string, diff)
	if same(file_name, string)
		if diff
			puts "nothing has changed between '#{file_name}' and what is in the definitions\n\n"
		else
			puts "not writing to '#{file_name}', nothing has changed\n\n"
		end
	else
		if diff
			puts "##### differences between the definition and '#{file_name}' are:\n"
			difference(file_name, string)
			puts "##### end of diff\n\n"
		else
			puts "writing '#{file_name}'\n\n"
		
			file = File.new(file_name, 'w')
			file.write(string)
			file.close()
		end
	end
end

def same(file_name, string)
	file = File.new(file_name)
	result = (file.read() == string)
	file.close()
	return result
end

def difference(file_name, string)
	tmp_name = ".generate.tmp"
	gen_file = File.new(tmp_name, "w")
	gen_file.write(string)
	gen_file.close()

	system("diff #{file_name} #{tmp_name}")
end


puts <<EOS

	Code and documentation generating script for the interpreter of KTurtle
	by Cies Breijs
	
	This script, "generate.rb", makes sure the definitions, as stored in
	"definitions.rb", are parsed into the code of the interpreter.
	This scripts is only used by developers, and should not be
	distributed in binary packages.\n
	All changes to the definitions should be made in "definitions.rb".\n
	Use the 'diff' command line option (./generate.rb diff) to see the
	differences.\n
	For more information on the workings see the source of "generate.rb".
\n
EOS

make_headers()
require('./definitions.rb') # here the definitions of the commands are stored
make_footers()


for arg in ARGV
	if arg =~ /diff/
		write_files(true)
		exit
	end
end
write_files(false)

puts "\nTotal generated lines of code: #{@total_generated_lines.to_s}\n\n"

